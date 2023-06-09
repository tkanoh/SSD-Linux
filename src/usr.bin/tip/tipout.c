/*	$ssdlinux: tipout.c,v 1.1 2004/11/12 15:22:13 kanoh Exp $	*/
/*	$NetBSD: tipout.c,v 1.8 2003/08/07 11:16:20 agc Exp $	*/

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
static char sccsid[] = "@(#)tipout.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: tipout.c,v 1.8 2003/08/07 11:16:20 agc Exp $");
#endif /* not lint */
#endif

#include "tip.h"
/*
 * tip
 *
 * lower fork of tip -- handles passive side
 *  reading from the remote host
 */

static	jmp_buf sigbuf;

void	intEMT __P((int));
void	intIOT __P((int));
void	intSYS __P((int));
void	intTERM __P((int));

/*
 * TIPOUT wait state routine --
 *   sent by TIPIN when it wants to posses the remote host
 */
void
intIOT(dummy)
	int dummy;
{

	write(repdes[1],&ccc,1);
	read(fildes[0], &ccc,1);
	longjmp(sigbuf, 1);
}

/*
 * Scripting command interpreter --
 *  accepts script file name over the pipe and acts accordingly
 */
void
intEMT(dummy)
	int dummy;
{
	char c, line[256];
	char *pline = line;
	char reply;

	read(fildes[0], &c, 1);
	while (c != '\n' && line + sizeof line - pline > 0) {
		*pline++ = c;
		read(fildes[0], &c, 1);
	}
	*pline = '\0';
	if (boolean(value(SCRIPT)) && fscript != NULL)
		fclose(fscript);
	if (pline == line) {
		setboolean(value(SCRIPT), FALSE);
		reply = 'y';
	} else {
		if ((fscript = fopen(line, "a")) == NULL)
			reply = 'n';
		else {
			reply = 'y';
			setboolean(value(SCRIPT), TRUE);
		}
	}
	write(repdes[1], &reply, 1);
	longjmp(sigbuf, 1);
}

void
intTERM(dummy)
	int dummy;
{

	if (boolean(value(SCRIPT)) && fscript != NULL)
		fclose(fscript);
	exit(0);
}

void
intSYS(dummy)
	int dummy;
{

	setboolean(value(BEAUTIFY), !boolean(value(BEAUTIFY)));
	longjmp(sigbuf, 1);
}

/*
 * ****TIPOUT   TIPOUT****
 */
void
tipout()
{
	char buf[BUFSIZ];
	char *cp;
	int cnt;
	int omask;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
#if 0
	signal(SIGEMT, intEMT);		/* attention from TIPIN */
#endif
	signal(SIGTERM, intTERM);	/* time to go signal */
	signal(SIGIOT, intIOT);		/* scripting going on signal */
	signal(SIGHUP, intTERM);	/* for dial-ups */
	signal(SIGSYS, intSYS);		/* beautify toggle */
	(void) setjmp(sigbuf);
	for (omask = 0;; sigsetmask(omask)) {
		cnt = read(FD, buf, BUFSIZ);
		if (cnt <= 0) {
			/* lost carrier */
			if (cnt < 0 && errno == EIO) {
				sigblock(sigmask(SIGTERM));
				intTERM(0);
				/*NOTREACHED*/
			}
			continue;
		}
#if 0
#define	ALLSIGS	sigmask(SIGEMT)|sigmask(SIGTERM)|sigmask(SIGIOT)|sigmask(SIGSYS)
#else
#define	ALLSIGS	sigmask(SIGTERM)|sigmask(SIGIOT)|sigmask(SIGSYS)
#endif
		omask = sigblock(ALLSIGS);
		for (cp = buf; cp < buf + cnt; cp++)
			*cp &= STRIP_PAR;
		write(1, buf, cnt);
		if (boolean(value(SCRIPT)) && fscript != NULL) {
			if (!boolean(value(BEAUTIFY))) {
				fwrite(buf, 1, cnt, fscript);
				continue;
			}
			for (cp = buf; cp < buf + cnt; cp++)
				if ((*cp >= ' ' && *cp <= '~') ||
				    any(*cp, value(EXCEPTIONS)))
					putc(*cp, fscript);
		}
	}
}
