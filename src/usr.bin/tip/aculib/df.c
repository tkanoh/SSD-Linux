/*	$ssdlinux: df.c,v 1.1 2004/11/12 15:22:13 kanoh Exp $	*/
/*	$NetBSD: df.c,v 1.7 2004/04/23 22:11:44 christos Exp $	*/

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
static char sccsid[] = "@(#)df.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: df.c,v 1.7 2004/04/23 22:11:44 christos Exp $");
#endif /* not lint */
#endif

/*
 * Dial the DF02-AC or DF03-AC
 */

#include "tip.h"

static jmp_buf Sjbuf;

static	int	df_dialer __P((char *, char *, int));
static	void	timeout __P((int));

int
df02_dialer(num, acu)
	char *num, *acu;
{

	return (df_dialer(num, acu, 0));
}

int
df03_dialer(num, acu)
	char *num, *acu;
{

	return (df_dialer(num, acu, 1));
}

static int
df_dialer(num, acu, df03)
	char *num, *acu;
	int df03;
{
	int f = FD;
	struct termios cntrl;
	int spd = 0;
	char c = '\0';

#if __GNUC__	/* XXX pacify gcc */
	(void)&spd;
#endif

	tcgetattr(f, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(f, TCSANOW, &cntrl);
	if (setjmp(Sjbuf)) {
		printf("connection timed out\r\n");
		df_disconnect();
		return (0);
	}
	if (boolean(value(VERBOSE)))
		printf("\ndialing...");
	fflush(stdout);
#ifdef TIOCMSET
	if (df03) {
		int st = TIOCM_ST;	/* secondary Transmit flag */

		tcgetattr(f, &cntrl);
		spd = cfgetospeed(&cntrl);
		if (spd != B1200) {	/* must dial at 1200 baud */
			cfsetospeed(&cntrl, B1200);
			cfsetispeed(&cntrl, B1200);
			tcsetattr(f, TCSAFLUSH, &cntrl);
			ioctl(f, TIOCMBIC, &st); /* clear ST for 300 baud */
		} else
			ioctl(f, TIOCMBIS, &st); /* set ST for 1200 baud */
	}
#endif
	signal(SIGALRM, timeout);
	alarm(5 * strlen(num) + 10);
	tcflush(f, TCIOFLUSH);
	write(f, "\001", 1);
	sleep(1);
	write(f, "\002", 1);
	write(f, num, strlen(num));
	read(f, &c, 1);
#ifdef TIOCMSET
	if (df03 && spd != B1200) {
		cfsetospeed(&cntrl, spd);
		cfsetispeed(&cntrl, spd);
		tcsetattr(f, TCSAFLUSH, &cntrl);
	}
#endif
	return (c == 'A');
}

void
df_disconnect()
{

	write(FD, "\001", 1);
	sleep(1);
	tcflush(FD, TCIOFLUSH);
}


void
df_abort()
{

	df_disconnect();
}


static void
timeout(dummy)
	int dummy;
{

	longjmp(Sjbuf, 1);
}
