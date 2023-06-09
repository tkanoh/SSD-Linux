/*	$ssdlinux: hsearch.c,v 1.1 2004/11/11 17:13:56 kanoh Exp $	*/
/*	$NetBSD: hsearch.c,v 1.14 1999/02/16 18:23:00 kleink Exp $	*/

/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
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
#if defined(LIBC_SCCS) && !defined(lint)
#if 0
static char sccsid[] = "@(#)hsearch.c	8.4 (Berkeley) 7/21/94";
#else
__RCSID("$NetBSD: hsearch.c,v 1.14 1999/02/16 18:23:00 kleink Exp $");
#endif
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>

#include <fcntl.h>
#include <search.h>
#include <string.h>

#include <db.h>

static DB *dbp = NULL;
static ENTRY retval;

extern int
hcreate(nel)
	size_t nel;
{
	HASHINFO info;

	info.nelem = nel;
	info.bsize = 256;
	info.ffactor = 8;
	info.cachesize = 0;
	info.hash = NULL;
	info.lorder = 0;
	dbp = (DB *)__hash_open(NULL, O_CREAT | O_RDWR, 0600, &info, 0);
	return (dbp != NULL);
}

extern ENTRY *
hsearch(item, action)
	ENTRY item;
	ACTION action;
{
	DBT key, val;
	int status;

	if (!dbp)
		return (NULL);
	key.data = item.key;
	key.size = strlen((char *)item.key) + 1;

	if (action == ENTER) {
		val.data = item.data;
		val.size = strlen((char *)item.data) + 1;
		status = (dbp->put)(dbp, &key, &val, R_NOOVERWRITE);
		if (status)
			return (NULL);
	} else {
		/* FIND */
		status = (dbp->get)(dbp, &key, &val, 0);
		if (status)
			return (NULL);
		else
			item.data = val.data;
	}
	retval.key = item.key;
	retval.data = item.data;
	return (&retval);
}

extern void
hdestroy()
{
	if (dbp) {
		(void)(dbp->close)(dbp);
		dbp = NULL;
	}
}
