/*	$ssdlinux: fingerd.c,v 1.1.1.1 2002/05/02 13:37:07 kanoh Exp $	*/
/*	$NetBSD: fingerd.c,v 1.12 1999/09/26 10:08:43 kleink Exp $	*/

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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
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

#ifndef lint
static char const copyright[] =
"@(#) Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "from: @(#)fingerd.c	8.1 (Berkeley) 6/4/93";
#else
static char const rcsid[] = "$NetBSD: fingerd.c,v 1.12 1999/09/26 10:08:43 kleink Exp $";
#endif
#endif /* not lint */

#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <unistd.h>
#include <syslog.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathnames.h"

void err __P((const char *, ...));
int main __P((int, char *[]));

int
main(argc, argv)
	int argc;
	char *argv[];
{
	register FILE *fp;
	register int ch, ac = 2;
	register char *lp = NULL /* XXX gcc */;
	struct sockaddr_storage ss;
	int p[2], logging, no_forward, user_required, short_list, sval;
#define	ENTRIES	50
	char **ap, *av[ENTRIES + 1], **comp, line[1024], *prog, *s;
	char hostbuf[MAXHOSTNAMELEN];

	prog = _PATH_FINGER;
	logging = no_forward = user_required = short_list = 0;
	openlog("fingerd", LOG_PID, LOG_DAEMON);
	opterr = 0;
	while ((ch = getopt(argc, argv, "gsluShmpP:")) != -1)
		switch (ch) {
		case 'l':
			logging = 1;
			break;
		case 'P':
			prog = optarg;
			break;
		case 's':
			no_forward = 1;
			break;
		case 'u':
			user_required = 1;
			break;
		case 'S':
			short_list = 1;
			av[ac++] = "-s";
			break;
		case 'h':
			av[ac++] = "-h";
			break;
		case 'm':
			av[ac++] = "-m";
			break;
		case 'p':
			av[ac++] = "-p";
			break;
		case 'g':
			av[ac++] = "-g";
			break;
		case '?':
		default:
			err("illegal option -- %c", ch);
		}


	if (logging) {
		sval = sizeof(ss);
		if (getpeername(0, (struct sockaddr *)&ss, &sval) < 0)
			err("getpeername: %s", strerror(errno));
		(void)getnameinfo((struct sockaddr *)&ss, sval,
				hostbuf, sizeof(hostbuf), NULL, 0, 0);
		lp = hostbuf;
	}
	
	if (!fgets(line, sizeof(line), stdin)) {
		if (logging)
			syslog(LOG_NOTICE, "query from %s", lp);
		exit(1);
	}
	while ((s = strrchr(line, '\n')) != NULL ||
	    (s = strrchr(line, '\r')) != NULL)
		*s = '\0';

	if (logging) {
		if (*line == '\0')
			syslog(LOG_NOTICE, "query from %s", lp);
		else
			syslog(LOG_NOTICE, "query from %s: %s", lp, line);
	}

	av[ac++] = "--";
	comp = &av[1];
	for (lp = line, ap = &av[ac]; ac < ENTRIES;) {
		if ((*ap = strtok(lp, " \t\r\n")) == NULL)
			break;
		lp = NULL;
		if (no_forward && strchr(*ap, '@')) {
			(void) puts("fowarding service denied\r\n");
			exit(1);
		}

		ch = strlen(*ap);
		while ((*ap)[ch-1] == '@')
			(*ap)[--ch] = '\0';
		if (**ap == '\0')
			continue;

		/* RFC1196: "/[Ww]" == "-l" */
		if ((*ap)[0] == '/' && ((*ap)[1] == 'W' || (*ap)[1] == 'w')) {
			if (!short_list) {
				av[1] = "-l";
				comp = &av[0];
			}
		} else {
			ap++;
			ac++;
		}
	}
	av[ENTRIES - 1] = NULL;

	if ((lp = strrchr(prog, '/')))
		*comp = ++lp;
	else
		*comp = prog;

	if (user_required) {
		for (ap = comp + 1; strcmp("--", *(ap++)); );
		if (*ap == NULL) {
			(void) puts("must provide username\r\n");
			exit(1);
		}
	}

	if (pipe(p) < 0)
		err("pipe: %s", strerror(errno));

	switch(fork()) {
	case 0:
		(void) close(p[0]);
		if (p[1] != 1) {
			(void) dup2(p[1], 1);
			(void) close(p[1]);
		}
		execv(prog, comp);
		err("execv: %s: %s", prog, strerror(errno));
		_exit(1);
	case -1:
		err("fork: %s", strerror(errno));
	}
	(void) close(p[1]);
	if (!(fp = fdopen(p[0], "r")))
		err("fdopen: %s", strerror(errno));
	while ((ch = getc(fp)) != EOF) {
		if (ch == '\n')
			putchar('\r');
		putchar(ch);
	}
	exit(0);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void) vsyslog(LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
	/* NOTREACHED */
}
