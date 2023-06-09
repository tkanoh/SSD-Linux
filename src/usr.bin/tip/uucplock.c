/*	$ssdlinux: uucplock.c,v 1.1 2004/11/12 15:22:13 kanoh Exp $	*/
/*	$NetBSD: uucplock.c,v 1.12 2004/04/23 22:11:44 christos Exp $	*/

/*
 * Copyright (c) 1988, 1993
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
static char sccsid[] = "@(#)uucplock.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: uucplock.c,v 1.12 2004/04/23 22:11:44 christos Exp $");
#endif /* not lint */
#endif

#include "pathnames.h"
#include "tip.h"

/* 
 * uucp style locking routines
 * return: 0 - success
 * 	  -1 - failure
 */

int
uu_lock(ttname)
	char *ttname;
{
	int fd, mypid;
	char tbuf[sizeof(_PATH_LOCKDIRNAME) + MAXNAMLEN];
	char text_pid[81];
	int len;

	(void)snprintf(tbuf, sizeof tbuf, _PATH_LOCKDIRNAME, ttname);
	fd = open(tbuf, O_RDWR|O_CREAT|O_EXCL, 0660);
	if (fd < 0) {
		/*
		 * file is already locked
		 * check to see if the process holding the lock still exists
		 */
		fd = open(tbuf, O_RDWR, 0);
		if (fd < 0) {
			perror(tbuf);
			fprintf(stderr, "Can't open lock file.\n");
			return(-1);
		}
		len = read(fd, text_pid, sizeof(text_pid)-1);
		if(len <= 0) {
			perror(tbuf);
			(void)close(fd);
			fprintf(stderr, "Can't read lock file.\n");
			return(-1);
		}
		text_pid[len] = 0;
		mypid = atol(text_pid);

		if (kill(mypid, 0) == 0 || errno != ESRCH) {
			(void)close(fd);	/* process is still running */
			return(-1);
		}
		/*
		 * The process that locked the file isn't running, so
		 * we'll lock it ourselves
		 */
		fprintf(stderr, "Stale lock on %s PID=%d... overriding.\n",
			ttname, mypid);
		if (lseek(fd, (off_t)0, SEEK_SET) < 0) {
			perror(tbuf);
			(void)close(fd);
			fprintf(stderr, "Can't seek lock file.\n");
			return(-1);
		}
		/* fall out and finish the locking process */
	}
	mypid = getpid();
	(void)snprintf(text_pid, sizeof text_pid, "%10d\n", mypid);
	len = strlen(text_pid);
	if (write(fd, text_pid, len) != len) {
		(void)close(fd);
		(void)unlink(tbuf);
		perror("lock write");
		return(-1);
	}
	(void)close(fd);
	return(0);
}

int
uu_unlock(ttname)
	char *ttname;
{
	char tbuf[sizeof(_PATH_LOCKDIRNAME) + MAXNAMLEN];

	(void)snprintf(tbuf, sizeof tbuf, _PATH_LOCKDIRNAME, ttname);
	return(unlink(tbuf));
}
