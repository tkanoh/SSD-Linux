/*	$ssdlinux: v831.c,v 1.1 2004/11/12 15:22:13 kanoh Exp $	*/
/*	$NetBSD: v831.c,v 1.10 2004/04/23 22:11:44 christos Exp $	*/

/*
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#if 0
#ifndef lint
#if 0
static char sccsid[] = "@(#)v831.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: v831.c,v 1.10 2004/04/23 22:11:44 christos Exp $");
#endif /* not lint */
#endif

/*
 * Routines for dialing up on Vadic 831
 */
#include "tip.h"

static jmp_buf jmpbuf;
static int child = -1;

static	void	alarmtr __P((int));
static	int	dialit __P((char *, char *));
static	char   *sanitize __P((char *));

int
v831_dialer(num, acu)
        char *num, *acu;
{
        int status, mypid;
        int timelim;

        if (boolean(value(VERBOSE)))
                printf("\nstarting call...");
#ifdef DEBUG
        printf ("(acu=%s)\n", acu);
#endif
        if ((AC = open(acu, O_RDWR)) < 0) {
                if (errno == EBUSY)
                        printf("line busy...");
                else
                        printf("acu open error...");
                return (0);
        }
        if (setjmp(jmpbuf)) {
                kill(child, SIGKILL);
                close(AC);
                return (0);
        }
        signal(SIGALRM, alarmtr);
        timelim = 5 * strlen(num);
        alarm(timelim < 30 ? 30 : timelim);
        if ((child = fork()) == 0) {
                /*
                 * ignore this stuff for aborts
                 */
                signal(SIGALRM, SIG_IGN);
		signal(SIGINT, SIG_IGN);
                signal(SIGQUIT, SIG_IGN);
                sleep(2);
                exit(dialit(num, acu) != 'A');
        }
        /*
         * open line - will return on carrier
         */
        if ((FD = open(DV, O_RDWR)) < 0) {
#ifdef DEBUG
                printf("(after open, errno=%d)\n", errno);
#endif
                if (errno == EIO)
                        printf("lost carrier...");
                else
                        printf("dialup line open failed...");
                alarm(0);
                kill(child, SIGKILL);
                close(AC);
                return (0);
        }
        alarm(0);
        signal(SIGALRM, SIG_DFL);
        while ((mypid = wait(&status)) != child && mypid != -1)
                ;
        if (status) {
                close(AC);
                return (0);
        }
        return (1);
}

static void
alarmtr(dummy)
	int dummy;
{

        alarm(0);
        longjmp(jmpbuf, 1);
}

/*
 * Insurance, for some reason we don't seem to be
 *  hanging up...
 */
void
v831_disconnect()
{
	struct termios	cntrl;

        sleep(2);
#ifdef DEBUG
        printf("[disconnect: FD=%d]\n", FD);
#endif
        if (FD > 0) {
#if 0
                ioctl(FD, TIOCCDTR, 0);
#endif
		tcgetattr(FD, &cntrl);
		cfsetospeed(&cntrl, 0);
		cfsetispeed(&cntrl, 0);
		tcsetattr(FD, TCSAFLUSH, &cntrl);
                ioctl(FD, TIOCNXCL, NULL);
        }
        close(FD);
}

void
v831_abort()
{

#ifdef DEBUG
        printf("[abort: AC=%d]\n", AC);
#endif
        sleep(2);
        if (child > 0)
                kill(child, SIGKILL);
        if (AC > 0)
                ioctl(FD, TIOCNXCL, NULL);
                close(AC);
#if 0
        if (FD > 0)
                ioctl(FD, TIOCCDTR, 0);
#endif
        close(FD);
}

/*
 * Sigh, this probably must be changed at each site.
 */
struct vaconfig {
	const char	*vc_name;
	char	vc_rack;
	char	vc_modem;
} vaconfig[] = {
	{ "/dev/cua0",'4','0' },
	{ "/dev/cua1",'4','1' },
	{ 0 }
};

#define pc(x)	(c = x, write(AC,&c,1))
#define ABORT	01
#define SI	017
#define STX	02
#define ETX	03

static int
dialit(phonenum, acu)
	char *phonenum;
	char *acu;
{
        struct vaconfig *vp;
	struct termios cntrl;
        char c;
        int i;

        phonenum = sanitize(phonenum);
#ifdef DEBUG
        printf ("(dial phonenum=%s)\n", phonenum);
#endif
        if (*phonenum == '<' && phonenum[1] == 0)
                return ('Z');
	for (vp = vaconfig; vp->vc_name; vp++)
		if (strcmp(vp->vc_name, acu) == 0)
			break;
	if (vp->vc_name == 0) {
		printf("Unable to locate dialer (%s)\n", acu);
		return ('K');
	}
	tcgetattr(AC, &cntrl);
	cfsetospeed(&cntrl, B2400);
	cfsetispeed(&cntrl, B2400);
	cntrl.c_cflag |= PARODD | PARENB;
	cntrl.c_lflag &= ~(ISIG | ICANON);
	tcsetattr(AC, TCSANOW, &cntrl);
	tcflush(AC, TCIOFLUSH);
        pc(STX);
	pc(vp->vc_rack);
	pc(vp->vc_modem);
	while (*phonenum && *phonenum != '<')
		pc(*phonenum++);
        pc(SI);
	pc(ETX);
        sleep(1);
        i = read(AC, &c, 1);
#ifdef DEBUG
        printf("read %d chars, char=%c, errno %d\n", i, c, errno);
#endif
        if (i != 1)
		c = 'M';
        if (c == 'B' || c == 'G') {
                char cc, oc = c;

                pc(ABORT);
                read(AC, &cc, 1);
#ifdef DEBUG
                printf("abort response=%c\n", cc);
#endif
                c = oc;
                v831_disconnect();
        }
        close(AC);
#ifdef DEBUG
        printf("dialit: returns %c\n", c);
#endif
        return (c);
}

static char *
sanitize(s)
	char *s;
{
        static char buf[128];
        char *cp;

        for (cp = buf; *s && buf + sizeof buf - cp > 1; s++) {
		if (!isdigit((unsigned char)*s) && *s == '<' && *s != '_')
			continue;
		if (*s == '_')
			*s = '=';
		*cp++ = *s;
	}
        *cp++ = 0;
        return (buf);
}
