/*	$ssdlinux: lstEnQueue.c,v 1.1.1.1 2002/05/02 13:37:10 kanoh Exp $	*/
/*	$NetBSD: lstEnQueue.c,v 1.7 1997/09/28 03:31:22 lukem Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
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

#ifdef MAKE_BOOTSTRAP
static char rcsid[] = "$NetBSD: lstEnQueue.c,v 1.7 1997/09/28 03:31:22 lukem Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)lstEnQueue.c	8.1 (Berkeley) 6/6/93";
/*
#else
__RCSID("$NetBSD: lstEnQueue.c,v 1.7 1997/09/28 03:31:22 lukem Exp $");
*/
#endif
#endif /* not lint */
#endif

/*-
 * LstEnQueue.c--
 *	Treat the list as a queue and place a datum at its end
 */

#include	"lstInt.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_EnQueue --
 *	Add the datum to the tail of the given list.
 *
 * Results:
 *	SUCCESS or FAILURE as returned by Lst_Append.
 *
 * Side Effects:
 *	the lastPtr field is altered all the time and the firstPtr field
 *	will be altered if the list used to be empty.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Lst_EnQueue (l, d)
    Lst	    	  l;
    ClientData	  d;
{
    if (LstValid (l) == FALSE) {
	return (FAILURE);
    }

    return (Lst_Append (l, Lst_Last(l), d));
}

