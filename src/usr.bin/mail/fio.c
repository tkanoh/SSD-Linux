/*	$ssdlinux: fio.c,v 1.1.1.1 2002/05/02 13:37:11 kanoh Exp $	*/
/*	$NetBSD: fio.c,v 1.12 1998/12/19 16:32:34 christos Exp $	*/

/*
 * Copyright (c) 1980, 1993
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

#include <sys/cdefs.h>
/*
#ifndef lint
#if 0
static char sccsid[] = "@(#)fio.c	8.2 (Berkeley) 4/20/95";
#else
__RCSID("$NetBSD: fio.c,v 1.12 1998/12/19 16:32:34 christos Exp $");
#endif
#endif */ /* not lint */

#include "rcv.h"
#include "extern.h"

/*
 * Mail -- a mail program
 *
 * File I/O.
 */

/*
 * Set up the input pointers while copying the mail file into /tmp.
 */
void
setptr(ibuf, offset)
	FILE *ibuf;
	off_t offset;
{
	extern char *tmpdir;
	int c, count;
	char *cp, *cp2;
	struct message this;
	FILE *mestmp;
	int maybe, inhead;
	char linebuf[LINESIZE];
	int omsgCount;

	/* Get temporary file. */
	(void)snprintf(linebuf, LINESIZE, "%s/mail.XXXXXX", tmpdir);
	if ((c = mkstemp(linebuf)) == -1 ||
	    (mestmp = Fdopen(c, "r+")) == NULL) {
		(void)fprintf(stderr, "mail: can't open %s\n", linebuf);
		exit(1);
	}
	(void)unlink(linebuf);

	if (offset == 0) {
		 msgCount = 0;
	} else {
		/* Seek into the file to get to the new messages */
		(void) fseek(ibuf, offset, 0);
		/*
		 * We need to make "offset" a pointer to the end of
		 * the temp file that has the copy of the mail file.
		 * If any messages have been edited, this will be
		 * different from the offset into the mail file.
		 */
		(void) fseek(otf, 0L, 2);
		offset = ftell(otf);
	}
	omsgCount = msgCount;
	maybe = 1;
	inhead = 0;
	this.m_flag = MUSED|MNEW;
	this.m_size = 0;
	this.m_lines = 0;
	this.m_block = 0;
	this.m_offset = 0;
	for (;;) {
		if (fgets(linebuf, LINESIZE, ibuf) == NULL) {
			if (append(&this, mestmp)) {
				perror("temporary file");
				exit(1);
			}
			makemessage(mestmp, omsgCount);
			return;
		}
		count = strlen(linebuf);
		/*
		 * Transforms lines ending in <CR><LF> to just <LF>.
		 * This allows mail to be able to read Eudora mailboxes
		 * that reside on a DOS partition.
		 */
		if (count >= 2 && linebuf[count-1] == '\n' && linebuf[count-2] == '\r') {
			linebuf[count-2] = '\n';
			count--;
		}
		(void) fwrite(linebuf, sizeof *linebuf, count, otf);
		if (ferror(otf)) {
			perror("/tmp");
			exit(1);
		}
		if(count)
			linebuf[count - 1] = 0;
		if (maybe && linebuf[0] == 'F' && ishead(linebuf)) {
			msgCount++;
			if (append(&this, mestmp)) {
				perror("temporary file");
				exit(1);
			}
			this.m_flag = MUSED|MNEW;
			this.m_size = 0;
			this.m_lines = 0;
			this.m_block = blockof(offset);
			this.m_offset = offsetof(offset);
			inhead = 1;
		} else if (linebuf[0] == 0) {
			inhead = 0;
		} else if (inhead) {
			for (cp = linebuf, cp2 = "status";; cp++) {
				if ((c = *cp2++) == 0) {
					while (isspace((unsigned char)*cp++))
						;
					if (cp[-1] != ':')
						break;
					while ((c = *cp++) != '\0')
						if (c == 'R')
							this.m_flag |= MREAD;
						else if (c == 'O')
							this.m_flag &= ~MNEW;
					inhead = 0;
					break;
				}
				if (*cp != c && *cp != toupper(c))
					break;
			}
		}
		offset += count;
		this.m_size += count;
		this.m_lines++;
		maybe = linebuf[0] == 0;
	}
}

/*
 * Drop the passed line onto the passed output buffer.
 * If a write error occurs, return -1, else the count of
 * characters written, including the newline if requested.
 */
int
putline(obuf, linebuf, outlf)
	FILE *obuf;
	char *linebuf;
	int   outlf;
{
	int c;

	c = strlen(linebuf);
	(void) fwrite(linebuf, sizeof *linebuf, c, obuf);
	if (outlf) {
		(void) putc('\n', obuf);
		c++;
	}
	if (ferror(obuf))
		return (-1);
	return (c);
}

/*
 * Read up a line from the specified input into the line
 * buffer.  Return the number of characters read.  Do not
 * include the newline at the end.
 */
int
readline(ibuf, linebuf, linesize)
	FILE *ibuf;
	char *linebuf;
	int linesize;
{
	int n;

	clearerr(ibuf);
	if (fgets(linebuf, linesize, ibuf) == NULL)
		return -1;
	n = strlen(linebuf);
	if (n > 0 && linebuf[n - 1] == '\n')
		linebuf[--n] = '\0';
	return n;
}

/*
 * Return a file buffer all ready to read up the
 * passed message pointer.
 */
FILE *
setinput(mp)
	struct message *mp;
{

	fflush(otf);
	if (fseek(itf, (long)positionof(mp->m_block, mp->m_offset), 0) < 0)
		err(1, "fseek");
	return (itf);
}

/*
 * Take the data out of the passed ghost file and toss it into
 * a dynamically allocated message structure.
 */
void
makemessage(f, omsgCount)
	FILE *f;
	int omsgCount;
{
	int size = (msgCount + 1) * sizeof (struct message);

	if (omsgCount) {
		message = (struct message *)realloc(message, (unsigned) size);
		if (message == 0)
			errx(1, "Insufficient memory for %d messages\n",
			      msgCount);
	} else {        
		if (message != 0)
			free((char *) message);
		if ((message = (struct message *) malloc((unsigned) size)) == 0)
			errx(1, "Insufficient memory for %d messages",
			    msgCount);
		dot = message;
	}
	size -= (omsgCount + 1) * sizeof (struct message);
	fflush(f);
	(void) lseek(fileno(f), (off_t)sizeof *message, 0);
	if (read(fileno(f), (char *) &message[omsgCount], size) != size)
		errx(1, "Message temporary file corrupted");
	message[msgCount].m_size = 0;
	message[msgCount].m_lines = 0;
	Fclose(f);
}

/*
 * Append the passed message descriptor onto the temp file.
 * If the write fails, return 1, else 0
 */
int
append(mp, f)
	struct message *mp;
	FILE *f;
{
	return fwrite((char *) mp, sizeof *mp, 1, f) != 1;
}

/*
 * Delete a file, but only if the file is a plain file.
 */
int
rm(name)
	char *name;
{
	struct stat sb;

	if (stat(name, &sb) < 0)
		return(-1);
	if (!S_ISREG(sb.st_mode)) {
		errno = EISDIR;
		return(-1);
	}
	return(unlink(name));
}

static int sigdepth;		/* depth of holdsigs() */
static sigset_t nset, oset;
/*
 * Hold signals SIGHUP, SIGINT, and SIGQUIT.
 */
void
holdsigs()
{

	if (sigdepth++ == 0) {
		sigemptyset(&nset);
		sigaddset(&nset, SIGHUP);
		sigaddset(&nset, SIGINT);
		sigaddset(&nset, SIGQUIT);
		sigprocmask(SIG_BLOCK, &nset, &oset);
	}
}

/*
 * Release signals SIGHUP, SIGINT, and SIGQUIT.
 */
void
relsesigs()
{

	if (--sigdepth == 0)
		sigprocmask(SIG_SETMASK, &oset, NULL);
}

/*
 * Determine the size of the file possessed by
 * the passed buffer.
 */
off_t
fsize(iob)
	FILE *iob;
{
	struct stat sbuf;

	if (fstat(fileno(iob), &sbuf) < 0)
		return 0;
	return sbuf.st_size;
}

/*
 * Evaluate the string given as a new mailbox name.
 * Supported meta characters:
 *	%	for my system mail box
 *	%user	for user's system mail box
 *	#	for previous file
 *	&	invoker's mbox file
 *	+file	file in folder directory
 *	any shell meta character
 * Return the file name as a dynamic string.
 */
char *
expand(name)
	char *name;
{
	char xname[PATHSIZE];
	char cmdbuf[PATHSIZE];		/* also used for file names */
	int pid, l;
	char *cp, *shell;
	int pivec[2];
	struct stat sbuf;
	extern int wait_status;

	/*
	 * The order of evaluation is "%" and "#" expand into constants.
	 * "&" can expand into "+".  "+" can expand into shell meta characters.
	 * Shell meta characters expand into constants.
	 * This way, we make no recursive expansion.
	 */
	switch (*name) {
	case '%':
		findmail(name[1] ? name + 1 : myname, xname);
		return savestr(xname);
	case '#':
		if (name[1] != 0)
			break;
		if (prevfile[0] == 0) {
			printf("No previous file\n");
			return NOSTR;
		}
		return savestr(prevfile);
	case '&':
		if (name[1] == 0 && (name = value("MBOX")) == NOSTR)
			name = "~/mbox";
		/* fall through */
	}
	if (name[0] == '+' && getfold(cmdbuf) >= 0) {
		snprintf(xname, PATHSIZE, "%s/%s", cmdbuf, name + 1);
		name = savestr(xname);
	}
	/* catch the most common shell meta character */
	if (name[0] == '~' && (name[1] == '/' || name[1] == '\0')) {
		snprintf(xname, PATHSIZE, "%s%s", homedir, name + 1);
		name = savestr(xname);
	}
	if (!anyof(name, "~{[*?$`'\"\\"))
		return name;
	if (pipe(pivec) < 0) {
		perror("pipe");
		return name;
	}
	snprintf(cmdbuf, PATHSIZE, "echo %s", name);
	if ((shell = value("SHELL")) == NOSTR)
		shell = _PATH_CSHELL;
	pid = start_command(shell, 0, -1, pivec[1], "-c", cmdbuf, NOSTR);
	if (pid < 0) {
		close(pivec[0]);
		close(pivec[1]);
		return NOSTR;
	}
	close(pivec[1]);
	l = read(pivec[0], xname, PATHSIZE);
	close(pivec[0]);
	if (wait_child(pid) < 0 && WTERMSIG(wait_status) != SIGPIPE) {
		fprintf(stderr, "\"%s\": Expansion failed.\n", name);
		return NOSTR;
	}
	if (l < 0) {
		perror("read");
		return NOSTR;
	}
	if (l == 0) {
		fprintf(stderr, "\"%s\": No match.\n", name);
		return NOSTR;
	}
	if (l == PATHSIZE) {
		fprintf(stderr, "\"%s\": Expansion buffer overflow.\n", name);
		return NOSTR;
	}
	xname[l] = '\0';
	for (cp = &xname[l-1]; *cp == '\n' && cp > xname; cp--)
		;
	cp[1] = '\0';
	if (strchr(xname, ' ') && stat(xname, &sbuf) < 0) {
		fprintf(stderr, "\"%s\": Ambiguous.\n", name);
		return NOSTR;
	}
	return savestr(xname);
}

/*
 * Determine the current folder directory name.
 */
int
getfold(name)
	char *name;
{
	char *folder;

	if ((folder = value("folder")) == NOSTR)
		return (-1);
	if (*folder == '/') {
		strncpy(name, folder, PATHSIZE - 1);
		name[PATHSIZE - 1] = '\0' ;
	}
	else
		snprintf(name, PATHSIZE, "%s/%s", homedir, folder);
	return (0);
}

/*
 * Return the name of the dead.letter file.
 */
char *
getdeadletter()
{
	char *cp;

	if ((cp = value("DEAD")) == NOSTR || (cp = expand(cp)) == NOSTR)
		cp = expand("~/dead.letter");
	else if (*cp != '/') {
		char buf[PATHSIZE];

		(void) snprintf(buf, PATHSIZE, "~/%s", cp);
		cp = expand(buf);
	}
	return cp;
}
