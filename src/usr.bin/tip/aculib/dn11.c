/*	$ssdlinux: dn11.c,v 1.1 2004/11/12 15:22:13 kanoh Exp $	*/
/*	$NetBSD: dn11.c,v 1.8 2004/03/11 03:33:19 uebayasi Exp $	*/

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
static char sccsid[] = "@(#)dn11.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: dn11.c,v 1.8 2004/03/11 03:33:19 uebayasi Exp $");
#endif /* not lint */
#endif

/*
 * Routines for dialing up on DN-11
 */
#include "tip.h"

static jmp_buf jmpbuf;
static int child = -1, dn;

static	void	alarmtr __P((int));

int
dn_dialer(num, acu)
	char *num, *acu;
{
	int lt, nw;
	int timelim;
	struct termios cntrl;

	if (boolean(value(VERBOSE)))
		printf("\nstarting call...");
	if ((dn = open(acu, O_WRONLY)) < 0) {
		if (errno == EBUSY)
			printf("line busy...");
		else
			printf("acu open error...");
		return (0);
	}
	if (setjmp(jmpbuf)) {
		kill(child, SIGKILL);
		close(dn);
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
		nw = write(dn, num, lt = strlen(num));
		exit(nw != lt);
	}
	/*
	 * open line - will return on carrier
	 */
	if ((FD = open(DV, O_RDWR)) < 0) {
		if (errno == EIO)
			printf("lost carrier...");
		else
			printf("dialup line open failed...");
		alarm(0);
		kill(child, SIGKILL);
		close(dn);
		return (0);
	}
	alarm(0);
	tcgetattr(dn, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(dn, TCSANOW, &cntrl);
	signal(SIGALRM, SIG_DFL);
	while ((nw = wait(&lt)) != child && nw != -1)
		;
	fflush(stdout);
	close(dn);
	if (lt != 0) {
		close(FD);
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
dn_disconnect()
{

	sleep(2);
#if 0
	if (FD > 0)
		ioctl(FD, TIOCCDTR, 0);
#endif
	close(FD);
}

void
dn_abort()
{

	sleep(2);
	if (child > 0)
		kill(child, SIGKILL);
	if (dn > 0)
		close(dn);
#if 0 
	if (FD > 0)
		ioctl(FD, TIOCCDTR, 0);
#endif
	close(FD);
}
