/*	$ssdlinux: quit.c,v 1.1.1.1 2002/05/02 13:37:11 kanoh Exp $	*/
/*	$NetBSD: quit.c,v 1.10 1997/12/07 21:27:10 bad Exp $	*/

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
static char sccsid[] = "@(#)quit.c	8.2 (Berkeley) 4/28/95";
#else
__RCSID("$NetBSD: quit.c,v 1.10 1997/12/07 21:27:10 bad Exp $");
#endif
#endif */ /* not lint */

#include "rcv.h"
#include "extern.h"

/*
 * Rcv -- receive mail rationally.
 *
 * Termination processing.
 */

/*
 * The "quit" command.
 */
int
quitcmd(v)
	void *v;
{
	/*
	 * If we are sourcing, then return 1 so execute() can handle it.
	 * Otherwise, return -1 to abort command loop.
	 */
	if (sourcing)
		return 1;
	return -1;
}

/*
 * Save all of the undetermined messages at the top of "mbox"
 * Save all untouched messages back in the system mailbox.
 * Remove the system mailbox, if none saved there.
 */
void
quit()
{
	int mcount, p, modify, autohold, anystat, holdbit, nohold;
	FILE *ibuf = NULL, *obuf, *fbuf, *rbuf, *readstat = NULL, *abuf;
	struct message *mp;
	int c;
	extern char *tempQuit, *tempResid;
	struct stat minfo;
	char *mbox;

#ifdef __GNUC__
	obuf = NULL;		/* XXX gcc -Wuninitialized */
#endif

	/*
	 * If we are read only, we can't do anything,
	 * so just return quickly.
	 */
	if (readonly)
		return;
	/*
	 * If editing (not reading system mail box), then do the work
	 * in edstop()
	 */
	if (edit) {
		edstop();
		return;
	}

	/*
	 * See if there any messages to save in mbox.  If no, we
	 * can save copying mbox to /tmp and back.
	 *
	 * Check also to see if any files need to be preserved.
	 * Delete all untouched messages to keep them out of mbox.
	 * If all the messages are to be preserved, just exit with
	 * a message.
	 */

	fbuf = Fopen(mailname, "r");
	if (fbuf == NULL)
		goto newmail;
	if (flock(fileno(fbuf), LOCK_EX) == -1) {
nolock:
		perror("Unable to lock mailbox");
		Fclose(fbuf);
		return;
	}
	if (dot_lock(mailname, 1, stdout, ".") == -1)
		goto nolock;
	rbuf = NULL;
	if (fstat(fileno(fbuf), &minfo) >= 0 && minfo.st_size > mailsize) {
		printf("New mail has arrived.\n");
		rbuf = Fopen(tempResid, "w");
		if (rbuf == NULL || fbuf == NULL)
			goto newmail;
#ifdef APPEND
		fseek(fbuf, (long)mailsize, 0);
		while ((c = getc(fbuf)) != EOF)
			(void) putc(c, rbuf);
#else
		p = minfo.st_size - mailsize;
		while (p-- > 0) {
			c = getc(fbuf);
			if (c == EOF)
				goto newmail;
			(void) putc(c, rbuf);
		}
#endif
		(void) fflush(rbuf);
		if (ferror(rbuf)) {
			perror(tempResid);
			Fclose(rbuf);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
		Fclose(rbuf);
		if ((rbuf = Fopen(tempResid, "r")) == NULL)
			goto newmail;
		rm(tempResid);
	}

	/*
	 * Adjust the message flags in each message.
	 */

	anystat = 0;
	autohold = value("hold") != NOSTR;
	holdbit = autohold ? MPRESERVE : MBOX;
	nohold = MBOX|MSAVED|MDELETED|MPRESERVE;
	if (value("keepsave") != NOSTR)
		nohold &= ~MSAVED;
	for (mp = &message[0]; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MNEW) {
			mp->m_flag &= ~MNEW;
			mp->m_flag |= MSTATUS;
		}
		if (mp->m_flag & MSTATUS)
			anystat++;
		if ((mp->m_flag & MTOUCH) == 0)
			mp->m_flag |= MPRESERVE;
		if ((mp->m_flag & nohold) == 0)
			mp->m_flag |= holdbit;
	}
	modify = 0;
	if (Tflag != NOSTR) {
		if ((readstat = Fopen(Tflag, "w")) == NULL)
			Tflag = NOSTR;
	}
	for (c = 0, p = 0, mp = &message[0]; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MBOX)
			c++;
		if (mp->m_flag & MPRESERVE)
			p++;
		if (mp->m_flag & MODIFY)
			modify++;
		if (Tflag != NOSTR && (mp->m_flag & (MREAD|MDELETED)) != 0) {
			char *id;

			if ((id = hfield("article-id", mp)) != NOSTR)
				fprintf(readstat, "%s\n", id);
		}
	}
	if (Tflag != NOSTR)
		Fclose(readstat);
	if (p == msgCount && !modify && !anystat) {
		printf("Held %d message%s in %s\n",
			p, p == 1 ? "" : "s", mailname);
		Fclose(fbuf);
		dot_unlock(mailname);
		return;
	}
	if (c == 0) {
		if (p != 0) {
			writeback(rbuf);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
		goto cream;
	}

	/*
	 * Create another temporary file and copy user's mbox file
	 * darin.  If there is no mbox, copy nothing.
	 * If he has specified "append" don't copy his mailbox,
	 * just copy saveable entries at the end.
	 */

	mbox = expand("&");
	mcount = c;
	if (value("append") == NOSTR) {
		if ((obuf = Fopen(tempQuit, "w")) == NULL) {
			perror(tempQuit);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
		if ((ibuf = Fopen(tempQuit, "r")) == NULL) {
			perror(tempQuit);
			rm(tempQuit);
			Fclose(obuf);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
		rm(tempQuit);
		if ((abuf = Fopen(mbox, "r")) != NULL) {
			while ((c = getc(abuf)) != EOF)
				(void) putc(c, obuf);
			Fclose(abuf);
		}
		if (ferror(obuf)) {
			perror(tempQuit);
			Fclose(ibuf);
			Fclose(obuf);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
		Fclose(obuf);
		close(creat(mbox, 0600));
		if ((obuf = Fopen(mbox, "r+")) == NULL) {
			perror(mbox);
			Fclose(ibuf);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
	}
	else {
		if ((obuf = Fopen(mbox, "a")) == NULL) {
			perror(mbox);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
		fchmod(fileno(obuf), 0600);
	}
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if (mp->m_flag & MBOX)
			if (send(mp, obuf, saveignore, NOSTR) < 0) {
				perror(mbox);
				Fclose(ibuf);
				Fclose(obuf);
				Fclose(fbuf);
				dot_unlock(mailname);
				return;
			}

	/*
	 * Copy the user's old mbox contents back
	 * to the end of the stuff we just saved.
	 * If we are appending, this is unnecessary.
	 */

	if (value("append") == NOSTR) {
		rewind(ibuf);
		c = getc(ibuf);
		while (c != EOF) {
			(void) putc(c, obuf);
			if (ferror(obuf))
				break;
			c = getc(ibuf);
		}
		Fclose(ibuf);
	}
	fflush(obuf);
	if (!ferror(obuf))
		trunc(obuf);	/* XXX or should we truncate? */
	if (ferror(obuf)) {
		perror(mbox);
		Fclose(obuf);
		Fclose(fbuf);
		dot_unlock(mailname);
		return;
	}
	Fclose(obuf);
	if (mcount == 1)
		printf("Saved 1 message in mbox\n");
	else
		printf("Saved %d messages in mbox\n", mcount);

	/*
	 * Now we are ready to copy back preserved files to
	 * the system mailbox, if any were requested.
	 */

	if (p != 0) {
		writeback(rbuf);
		Fclose(fbuf);
		dot_unlock(mailname);
		return;
	}

	/*
	 * Finally, remove his /usr/mail file.
	 * If new mail has arrived, copy it back.
	 */

cream:
	if (rbuf != NULL) {
		abuf = Fopen(mailname, "r+");
		if (abuf == NULL)
			goto newmail;
		while ((c = getc(rbuf)) != EOF)
			(void) putc(c, abuf);
		(void) fflush(abuf);
		if (ferror(abuf)) {
			perror(mailname);
			Fclose(abuf);
			Fclose(fbuf);
			dot_unlock(mailname);
			return;
		}
		Fclose(rbuf);
		trunc(abuf);
		Fclose(abuf);
		alter(mailname);
		Fclose(fbuf);
		dot_unlock(mailname);
		return;
	}
	demail();
	Fclose(fbuf);
	dot_unlock(mailname);
	return;

newmail:
	printf("Thou hast new mail.\n");
	if (fbuf != NULL) {
		Fclose(fbuf);
		dot_unlock(mailname);
	}
}

/*
 * Preserve all the appropriate messages back in the system
 * mailbox, and print a nice message indicated how many were
 * saved.  On any error, just return -1.  Else return 0.
 * Incorporate the any new mail that we found.
 */
int
writeback(res)
	FILE *res;
{
	struct message *mp;
	int p, c;
	FILE *obuf;

	p = 0;
	if ((obuf = Fopen(mailname, "r+")) == NULL) {
		perror(mailname);
		return(-1);
	}
#ifndef APPEND
	if (res != NULL) {
		while ((c = getc(res)) != EOF)
			(void) putc(c, obuf);
		(void) fflush(obuf);
		if (ferror(obuf)) {
			perror(mailname);
			Fclose(obuf);
			return(-1);
		}
	}
#endif
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if ((mp->m_flag&MPRESERVE)||(mp->m_flag&MTOUCH)==0) {
			p++;
			if (send(mp, obuf, (struct ignoretab *)0, NOSTR) < 0) {
				perror(mailname);
				Fclose(obuf);
				return(-1);
			}
		}
#ifdef APPEND
	if (res != NULL)
		while ((c = getc(res)) != EOF)
			(void) putc(c, obuf);
#endif
	fflush(obuf);
	if (!ferror(obuf))
		trunc(obuf);	/* XXX or should we truncate? */
	if (ferror(obuf)) {
		perror(mailname);
		Fclose(obuf);
		return(-1);
	}
	if (res != NULL)
		Fclose(res);
	Fclose(obuf);
	alter(mailname);
	if (p == 1)
		printf("Held 1 message in %s\n", mailname);
	else
		printf("Held %d messages in %s\n", p, mailname);
	return(0);
}

/*
 * Terminate an editing session by attempting to write out the user's
 * file from the temporary.  Save any new stuff appended to the file.
 */
void
edstop()
{
	extern char *tmpdir;
	int gotcha, c;
	struct message *mp;
	FILE *obuf, *ibuf, *readstat = NULL;
	struct stat statb;
	char *tempname;

	if (readonly)
		return;
	holdsigs();
	if (Tflag != NOSTR) {
		if ((readstat = Fopen(Tflag, "w")) == NULL)
			Tflag = NOSTR;
	}
	for (mp = &message[0], gotcha = 0; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MNEW) {
			mp->m_flag &= ~MNEW;
			mp->m_flag |= MSTATUS;
		}
		if (mp->m_flag & (MODIFY|MDELETED|MSTATUS))
			gotcha++;
		if (Tflag != NOSTR && (mp->m_flag & (MREAD|MDELETED)) != 0) {
			char *id;

			if ((id = hfield("article-id", mp)) != NOSTR)
				fprintf(readstat, "%s\n", id);
		}
	}
	if (Tflag != NOSTR)
		Fclose(readstat);
	if (!gotcha || Tflag != NOSTR)
		goto done;
	ibuf = NULL;
	if (stat(mailname, &statb) >= 0 && statb.st_size > mailsize) {
		tempname = tempnam(tmpdir, "mbox");

		if ((obuf = Fopen(tempname, "w")) == NULL) {
			perror(tempname);
			relsesigs();
			reset(0);
		}
		if ((ibuf = Fopen(mailname, "r")) == NULL) {
			perror(mailname);
			Fclose(obuf);
			rm(tempname);
			relsesigs();
			reset(0);
		}
		fseek(ibuf, (long)mailsize, 0);
		while ((c = getc(ibuf)) != EOF)
			(void) putc(c, obuf);
		(void) fflush(obuf);
		if (ferror(obuf)) {
			perror(tempname);
			Fclose(obuf);
			Fclose(ibuf);
			rm(tempname);
			relsesigs();
			reset(0);
		}
		Fclose(ibuf);
		Fclose(obuf);
		if ((ibuf = Fopen(tempname, "r")) == NULL) {
			perror(tempname);
			rm(tempname);
			relsesigs();
			reset(0);
		}
		rm(tempname);
		free(tempname);
	}
	printf("\"%s\" ", mailname);
	fflush(stdout);
	if ((obuf = Fopen(mailname, "r+")) == NULL) {
		perror(mailname);
		relsesigs();
		reset(0);
	}
	trunc(obuf);
	c = 0;
	for (mp = &message[0]; mp < &message[msgCount]; mp++) {
		if ((mp->m_flag & MDELETED) != 0)
			continue;
		c++;
		if (send(mp, obuf, (struct ignoretab *) NULL, NOSTR) < 0) {
			perror(mailname);
			relsesigs();
			reset(0);
		}
	}
	gotcha = (c == 0 && ibuf == NULL);
	if (ibuf != NULL) {
		while ((c = getc(ibuf)) != EOF)
			(void) putc(c, obuf);
		Fclose(ibuf);
	}
	fflush(obuf);
	if (ferror(obuf)) {
		perror(mailname);
		relsesigs();
		reset(0);
	}
	Fclose(obuf);
	if (gotcha) {
		rm(mailname);
		printf("removed\n");
	} else
		printf("complete\n");
	fflush(stdout);

done:
	relsesigs();
}
