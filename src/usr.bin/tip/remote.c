/*	$ssdlinux: remote.c,v 1.1 2004/11/12 15:22:13 kanoh Exp $	*/
/*	$NetBSD: remote.c,v 1.11 2004/04/23 22:24:34 christos Exp $	*/

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
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
__COPYRIGHT("@(#) Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)remote.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: remote.c,v 1.11 2004/04/23 22:24:34 christos Exp $");
#endif /* not lint */
#endif

#include "pathnames.h"
#include "tip.h"
#include "getcap.h"

/*
 * Attributes to be gleened from remote host description
 *   data base.
 */
static char **caps[] = {
	&AT, &DV, &CM, &CU, &EL, &IE, &OE, &PN, &PR, &DI,
	&ES, &EX, &FO, &RC, &RE, &PA
};

static const char *capstrings[] = {
	"at", "dv", "cm", "cu", "el", "ie", "oe", "pn", "pr",
	"di", "es", "ex", "fo", "rc", "re", "pa", 0
};

static const char	*db_array[3] = { _PATH_REMOTE, 0, 0 };

#define cgetflag(f)	(cgetcap(bp, f, ':') != NULL)

static	void	getremcap __P((char *));

static char tiprecord[] = "tip.record";
static char wspace[] = "\t\n\b\f";

static void
getremcap(host)
	char *host;
{
	const char **p;
	char ***q;
	char *bp;
	char *rempath;
	int   status;

	rempath = getenv("REMOTE");
	if (rempath != NULL) {
		if (*rempath != '/')
			/* we have an entry */
			cgetset(rempath);
		else {	/* we have a path */
			db_array[1] = rempath;
			db_array[2] = _PATH_REMOTE;
		}
	}
	if ((status = cgetent(&bp, db_array, host)) < 0) {
		if (DV ||
		    (host[0] == '/' && access(DV = host, R_OK | W_OK) == 0)) {
			CU = DV;
			HO = host;
			HW = 1;
			DU = 0;
			if (!BR)
				BR = DEFBR;
			FS = DEFFS;
			return;
		}
		switch(status) {
		case -1:
			fprintf(stderr, "tip: unknown host %s\n", host);
			break;
		case -2:
			fprintf(stderr, 
			    "tip: can't open host description file\n");
			break;
		case -3:
			fprintf(stderr, 
			    "tip: possible reference loop in host description file\n");
			break;
		}
		exit(3);
	}

	for (p = capstrings, q = caps; *p != NULL; p++, q++)
		if (**q == NULL)
			cgetstr(bp, *p, *q);
	if (!BR && (cgetnum(bp, "br", &BR) == -1))
		BR = DEFBR;
	if (cgetnum(bp, "fs", &FS) == -1)
		FS = DEFFS;
	if (DU < 0)
		DU = 0;
	else
		DU = cgetflag("du");
	if (DV == NULL) {
		fprintf(stderr, "%s: missing device spec\n", host);
		exit(3);
	}
	if (DU && CU == NULL)
		CU = DV;
	if (DU && PN == NULL) {
		fprintf(stderr, "%s: missing phone number\n", host);
		exit(3);
	}

	HD = cgetflag("hd");

	/*
	 * This effectively eliminates the "hw" attribute
	 *   from the description file
	 */
	if (!HW)
		HW = (CU == NULL) || (DU && equal(DV, CU));
	HO = host;
	/*
	 * see if uppercase mode should be turned on initially
	 */
	if (cgetflag("ra"))
		setboolean(value(RAISE), 1);
	if (cgetflag("ec"))
		setboolean(value(ECHOCHECK), 1);
	if (cgetflag("be"))
		setboolean(value(BEAUTIFY), 1);
	if (cgetflag("nb"))
		setboolean(value(BEAUTIFY), 0);
	if (cgetflag("sc"))
		setboolean(value(SCRIPT), 1);
	if (cgetflag("tb"))
		setboolean(value(TABEXPAND), 1);
	if (cgetflag("vb"))
		setboolean(value(VERBOSE), 1);
	if (cgetflag("nv"))
		setboolean(value(VERBOSE), 0);
	if (cgetflag("ta"))
		setboolean(value(TAND), 1);
	if (cgetflag("nt"))
		setboolean(value(TAND), 0);
	if (cgetflag("rw"))
		setboolean(value(RAWFTP), 1);
	if (cgetflag("hd"))
		setboolean(value(HALFDUPLEX), 1);
	if (cgetflag("dc"))
		DC = 1;
	if (RE == NULL)
		RE = tiprecord;
	if (EX == NULL)
		EX = wspace;
	if (ES != NULL)
		vstring("es", ES);
	if (FO != NULL)
		vstring("fo", FO);
	if (PR != NULL)
		vstring("pr", PR);
	if (RC != NULL)
		vstring("rc", RC);
	if (cgetnum(bp, "dl", &DL) == -1)
		DL = 0;
	if (cgetnum(bp, "cl", &CL) == -1)
		CL = 0;
	if (cgetnum(bp, "et", &ET) == -1)
		ET = 10;
}

char *
getremote(host)
	char *host;
{
	char *cp;
	static char *next;
	static int lookedup = 0;

	if (!lookedup) {
		if (host == NULL && (host = getenv("HOST")) == NULL) {
			fprintf(stderr, "tip: no host specified\n");
			exit(3);
		}
		getremcap(host);
		next = DV;
		lookedup++;
	}
	/*
	 * We return a new device each time we're called (to allow
	 *   a rotary action to be simulated)
	 */
	if (next == NULL)
		return (NULL);
	if ((cp = strchr(next, ',')) == NULL) {
		DV = next;
		next = NULL;
	} else {
		*cp++ = '\0';
		DV = next;
		next = cp;
	}
	return (DV);
}
