/*	$ssdlinux: hunt.c,v 1.1 2004/11/12 15:22:12 kanoh Exp $	*/
/*	$NetBSD: hunt.c,v 1.10 2003/08/07 11:16:17 agc Exp $	*/

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
static char sccsid[] = "@(#)hunt.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: hunt.c,v 1.10 2003/08/07 11:16:17 agc Exp $");
#endif /* not lint */
#endif

#include "tip.h"

static	jmp_buf deadline;
static	int deadfl;

void	dead __P((int));

void
dead(dummy)
	int dummy;
{

	deadfl = 1;
	longjmp(deadline, 1);
}

int
hunt(name)
	char *name;
{
	char *cp;
	sig_t f;

	f = signal(SIGALRM, dead);
	while ((cp = getremote(name)) != NULL) {
		deadfl = 0;
		uucplock = strrchr(cp, '/')+1;
		if (uu_lock(uucplock) < 0)
			continue;
		/*
		 * Straight through call units, such as the BIZCOMP,
		 * VADIC and the DF, must indicate they're hardwired in
		 *  order to get an open file descriptor placed in FD.
		 * Otherwise, as for a DN-11, the open will have to
		 *  be done in the "open" routine.
		 */
		if (!HW)
			break;
		if (setjmp(deadline) == 0) {
			alarm(10);
			FD = open(cp, (O_RDWR | (DC ? O_NONBLOCK : 0)));
		}
		alarm(0);
		if (FD < 0) {
			perror(cp);
			deadfl = 1;
		}
		if (!deadfl) {
			struct termios cntrl;

			tcgetattr(FD, &cntrl);
			if (!DC)
				cntrl.c_cflag |= HUPCL;
			tcsetattr(FD, TCSAFLUSH, &cntrl);
			ioctl(FD, TIOCEXCL, 0);
			signal(SIGALRM, SIG_DFL);
			return (cp != NULL);
		}
		(void)uu_unlock(uucplock);
	}
	signal(SIGALRM, f);
	return (deadfl ? -1 : cp != NULL);
}
