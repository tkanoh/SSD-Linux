/*	$ssdlinux: strings.c,v 1.1.1.1 2002/05/02 13:37:11 kanoh Exp $	*/
/*	$NetBSD: strings.c,v 1.6 1997/10/19 05:03:54 lukem Exp $	*/

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
static char sccsid[] = "@(#)strings.c	8.1 (Berkeley) 6/6/93";
#else
__RCSID("$NetBSD: strings.c,v 1.6 1997/10/19 05:03:54 lukem Exp $");
#endif
#endif */ /* not lint */

/*
 * Mail -- a mail program
 *
 * String allocation routines.
 * Strings handed out here are reclaimed at the top of the command
 * loop each time, so they need not be freed.
 */

#include "rcv.h"
#include "extern.h"

/*
 * Allocate size more bytes of space and return the address of the
 * first byte to the caller.  An even number of bytes are always
 * allocated so that the space will always be on a word boundary.
 * The string spaces are of exponentially increasing size, to satisfy
 * the occasional user with enormous string size requests.
 */

char *
salloc(size)
	int size;
{
	char *t;
	int s;
	struct strings *sp;
	int index;

	s = size;
	s += (sizeof (char *) - 1);
	s &= ~(sizeof (char *) - 1);
	index = 0;
	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++) {
		if (sp->s_topFree == NOSTR && (STRINGSIZE << index) >= s)
			break;
		if (sp->s_nleft >= s)
			break;
		index++;
	}
	if (sp >= &stringdope[NSPACE])
		errx(1, "String too large");
	if (sp->s_topFree == NOSTR) {
		index = sp - &stringdope[0];
		sp->s_topFree = malloc(STRINGSIZE << index);
		if (sp->s_topFree == NOSTR)
			errx(1, "No room for space %d", index);
		sp->s_nextFree = sp->s_topFree;
		sp->s_nleft = STRINGSIZE << index;
	}
	sp->s_nleft -= s;
	t = sp->s_nextFree;
	sp->s_nextFree += s;
	return(t);
}

/*
 * Reset the string area to be empty.
 * Called to free all strings allocated
 * since last reset.
 */
void
sreset()
{
	struct strings *sp;
	int index;

	if (noreset)
		return;
	index = 0;
	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++) {
		if (sp->s_topFree == NOSTR)
			continue;
		sp->s_nextFree = sp->s_topFree;
		sp->s_nleft = STRINGSIZE << index;
		index++;
	}
}

/*
 * Make the string area permanent.
 * Meant to be called in main, after initialization.
 */
void
spreserve()
{
	struct strings *sp;

	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++)
		sp->s_topFree = NOSTR;
}
