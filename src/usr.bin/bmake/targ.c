/*	$ssdlinux: targ.c,v 1.1.1.1 2002/05/02 13:37:10 kanoh Exp $	*/
/*	$NetBSD: targ.c,v 1.24 2001/11/12 01:33:49 tv Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
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
static char rcsid[] = "$NetBSD: targ.c,v 1.24 2001/11/12 01:33:49 tv Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)targ.c	8.2 (Berkeley) 3/19/94";
/*
#else
__RCSID("$NetBSD: targ.c,v 1.24 2001/11/12 01:33:49 tv Exp $");
*/
#endif
#endif /* not lint */
#endif

/*-
 * targ.c --
 *	Functions for maintaining the Lst allTargets. Target nodes are
 * kept in two structures: a Lst, maintained by the list library, and a
 * hash table, maintained by the hash library.
 *
 * Interface:
 *	Targ_Init 	    	Initialization procedure.
 *
 *	Targ_End 	    	Cleanup the module
 *
 *	Targ_List 	    	Return the list of all targets so far.
 *
 *	Targ_NewGN	    	Create a new GNode for the passed target
 *	    	  	    	(string). The node is *not* placed in the
 *	    	  	    	hash table, though all its fields are
 *	    	  	    	initialized.
 *
 *	Targ_FindNode	    	Find the node for a given target, creating
 *	    	  	    	and storing it if it doesn't exist and the
 *	    	  	    	flags are right (TARG_CREATE)
 *
 *	Targ_FindList	    	Given a list of names, find nodes for all
 *	    	  	    	of them. If a name doesn't exist and the
 *	    	  	    	TARG_NOCREATE flag was given, an error message
 *	    	  	    	is printed. Else, if a name doesn't exist,
 *	    	  	    	its node is created.
 *
 *	Targ_Ignore	    	Return TRUE if errors should be ignored when
 *	    	  	    	creating the given target.
 *
 *	Targ_Silent	    	Return TRUE if we should be silent when
 *	    	  	    	creating the given target.
 *
 *	Targ_Precious	    	Return TRUE if the target is precious and
 *	    	  	    	should not be removed if we are interrupted.
 *
 * Debugging:
 *	Targ_PrintGraph	    	Print out the entire graphm all variables
 *	    	  	    	and statistics for the directory cache. Should
 *	    	  	    	print something for suffixes, too, but...
 */

#include	  <stdio.h>
#include	  <time.h>
#include	  "make.h"
#include	  "hash.h"
#include	  "dir.h"

static Lst        allTargets;	/* the list of all targets found so far */
#ifdef CLEANUP
static Lst	  allGNs;	/* List of all the GNodes */
#endif
static Hash_Table targets;	/* a hash table of same */

#define HTSIZE	191		/* initial size of hash table */

static int TargPrintOnlySrc __P((ClientData, ClientData));
static int TargPrintName __P((ClientData, ClientData));
static int TargPrintNode __P((ClientData, ClientData));
#ifdef CLEANUP
static void TargFreeGN __P((ClientData));
#endif
static int TargPropagateCohort __P((ClientData, ClientData));
static int TargPropagateNode __P((ClientData, ClientData));

/*-
 *-----------------------------------------------------------------------
 * Targ_Init --
 *	Initialize this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The allTargets list and the targets hash table are initialized
 *-----------------------------------------------------------------------
 */
void
Targ_Init ()
{
    allTargets = Lst_Init (FALSE);
    Hash_InitTable (&targets, HTSIZE);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_End --
 *	Finalize this module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All lists and gnodes are cleared
 *-----------------------------------------------------------------------
 */
void
Targ_End ()
{
#ifdef CLEANUP
    Lst_Destroy(allTargets, NOFREE);
    if (allGNs)
	Lst_Destroy(allGNs, TargFreeGN);
    Hash_DeleteTable(&targets);
#endif
}

/*-
 *-----------------------------------------------------------------------
 * Targ_List --
 *	Return the list of all targets
 *
 * Results:
 *	The list of all targets.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Lst
Targ_List ()
{
    return allTargets;
}

/*-
 *-----------------------------------------------------------------------
 * Targ_NewGN  --
 *	Create and initialize a new graph node
 *
 * Results:
 *	An initialized graph node with the name field filled with a copy
 *	of the passed name
 *
 * Side Effects:
 *	The gnode is added to the list of all gnodes.
 *-----------------------------------------------------------------------
 */
GNode *
Targ_NewGN (name)
    char           *name;	/* the name to stick in the new node */
{
    register GNode *gn;

    gn = (GNode *) emalloc (sizeof (GNode));
    gn->name = estrdup (name);
    gn->uname = NULL;
    gn->path = (char *) 0;
    if (name[0] == '-' && name[1] == 'l') {
	gn->type = OP_LIB;
    } else {
	gn->type = 0;
    }
    gn->unmade =    	0;
    gn->made = 	    	UNMADE;
    gn->flags = 	0;
    gn->order =		0;
    gn->mtime = gn->cmtime = 0;
    gn->iParents =  	Lst_Init (FALSE);
    gn->cohorts =   	Lst_Init (FALSE);
    gn->parents =   	Lst_Init (FALSE);
    gn->children =  	Lst_Init (FALSE);
    gn->successors = 	Lst_Init (FALSE);
    gn->preds =     	Lst_Init (FALSE);
    Hash_InitTable(&gn->context, 0);
    gn->commands =  	Lst_Init (FALSE);
    gn->suffix =	NULL;
    gn->lineno =	0;
    gn->fname = 	NULL;

#ifdef CLEANUP
    if (allGNs == NULL)
	allGNs = Lst_Init(FALSE);
    Lst_AtEnd(allGNs, (ClientData) gn);
#endif

    return (gn);
}

#ifdef CLEANUP
/*-
 *-----------------------------------------------------------------------
 * TargFreeGN  --
 *	Destroy a GNode
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
static void
TargFreeGN (gnp)
    ClientData gnp;
{
    GNode *gn = (GNode *) gnp;


    free(gn->name);
    if (gn->uname)
	free(gn->uname);
    if (gn->path)
	free(gn->path);
    if (gn->fname)
	free(gn->fname);

    Lst_Destroy(gn->iParents, NOFREE);
    Lst_Destroy(gn->cohorts, NOFREE);
    Lst_Destroy(gn->parents, NOFREE);
    Lst_Destroy(gn->children, NOFREE);
    Lst_Destroy(gn->successors, NOFREE);
    Lst_Destroy(gn->preds, NOFREE);
    Hash_DeleteTable(&gn->context);
    Lst_Destroy(gn->commands, NOFREE);
    free((Address)gn);
}
#endif


/*-
 *-----------------------------------------------------------------------
 * Targ_FindNode  --
 *	Find a node in the list using the given name for matching
 *
 * Results:
 *	The node in the list if it was. If it wasn't, return NILGNODE of
 *	flags was TARG_NOCREATE or the newly created and initialized node
 *	if it was TARG_CREATE
 *
 * Side Effects:
 *	Sometimes a node is created and added to the list
 *-----------------------------------------------------------------------
 */
GNode *
Targ_FindNode (name, flags)
    char           *name;	/* the name to find */
    int             flags;	/* flags governing events when target not
				 * found */
{
    GNode         *gn;	      /* node in that element */
    Hash_Entry	  *he;	      /* New or used hash entry for node */
    Boolean	  isNew;      /* Set TRUE if Hash_CreateEntry had to create */
			      /* an entry for the node */


    if (flags & TARG_CREATE) {
	he = Hash_CreateEntry (&targets, name, &isNew);
	if (isNew) {
	    gn = Targ_NewGN (name);
	    Hash_SetValue (he, gn);
	    Var_Append(".ALLTARGETS", name, VAR_GLOBAL);
	    (void) Lst_AtEnd (allTargets, (ClientData)gn);
	}
    } else {
	he = Hash_FindEntry (&targets, name);
    }

    if (he == (Hash_Entry *) NULL) {
	return (NILGNODE);
    } else {
	return ((GNode *) Hash_GetValue (he));
    }
}

/*-
 *-----------------------------------------------------------------------
 * Targ_FindList --
 *	Make a complete list of GNodes from the given list of names
 *
 * Results:
 *	A complete list of graph nodes corresponding to all instances of all
 *	the names in names.
 *
 * Side Effects:
 *	If flags is TARG_CREATE, nodes will be created for all names in
 *	names which do not yet have graph nodes. If flags is TARG_NOCREATE,
 *	an error message will be printed for each name which can't be found.
 * -----------------------------------------------------------------------
 */
Lst
Targ_FindList (names, flags)
    Lst        	   names;	/* list of names to find */
    int            flags;	/* flags used if no node is found for a given
				 * name */
{
    Lst            nodes;	/* result list */
    register LstNode  ln;		/* name list element */
    register GNode *gn;		/* node in tLn */
    char    	  *name;

    nodes = Lst_Init (FALSE);

    if (Lst_Open (names) == FAILURE) {
	return (nodes);
    }
    while ((ln = Lst_Next (names)) != NILLNODE) {
	name = (char *)Lst_Datum(ln);
	gn = Targ_FindNode (name, flags);
	if (gn != NILGNODE) {
	    /*
	     * Note: Lst_AtEnd must come before the Lst_Concat so the nodes
	     * are added to the list in the order in which they were
	     * encountered in the makefile.
	     */
	    (void) Lst_AtEnd (nodes, (ClientData)gn);
	} else if (flags == TARG_NOCREATE) {
	    Error ("\"%s\" -- target unknown.", name);
	}
    }
    Lst_Close (names);
    return (nodes);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_Ignore  --
 *	Return true if should ignore errors when creating gn
 *
 * Results:
 *	TRUE if should ignore errors
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Ignore (gn)
    GNode          *gn;		/* node to check for */
{
    if (ignoreErrors || gn->type & OP_IGNORE) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Targ_Silent  --
 *	Return true if be silent when creating gn
 *
 * Results:
 *	TRUE if should be silent
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Silent (gn)
    GNode          *gn;		/* node to check for */
{
    if (beSilent || gn->type & OP_SILENT) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Targ_Precious --
 *	See if the given target is precious
 *
 * Results:
 *	TRUE if it is precious. FALSE otherwise
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
Boolean
Targ_Precious (gn)
    GNode          *gn;		/* the node to check */
{
    if (allPrecious || (gn->type & (OP_PRECIOUS|OP_DOUBLEDEP))) {
	return (TRUE);
    } else {
	return (FALSE);
    }
}

/******************* DEBUG INFO PRINTING ****************/

static GNode	  *mainTarg;	/* the main target, as set by Targ_SetMain */
/*-
 *-----------------------------------------------------------------------
 * Targ_SetMain --
 *	Set our idea of the main target we'll be creating. Used for
 *	debugging output.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	"mainTarg" is set to the main target's node.
 *-----------------------------------------------------------------------
 */
void
Targ_SetMain (gn)
    GNode   *gn;  	/* The main target we'll create */
{
    mainTarg = gn;
}

static int
TargPrintName (gnp, ppath)
    ClientData     gnp;
    ClientData	    ppath;
{
    GNode *gn = (GNode *) gnp;
    printf ("%s ", gn->name);
#ifdef notdef
    if (ppath) {
	if (gn->path) {
	    printf ("[%s]  ", gn->path);
	}
	if (gn == mainTarg) {
	    printf ("(MAIN NAME)  ");
	}
    }
#endif /* notdef */
    return (ppath ? 0 : 0);
}


int
Targ_PrintCmd (cmd, dummy)
    ClientData cmd;
    ClientData dummy;
{
    printf ("\t%s\n", (char *) cmd);
    return (dummy ? 0 : 0);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_FmtTime --
 *	Format a modification time in some reasonable way and return it.
 *
 * Results:
 *	The time reformatted.
 *
 * Side Effects:
 *	The time is placed in a static area, so it is overwritten
 *	with each call.
 *
 *-----------------------------------------------------------------------
 */
char *
Targ_FmtTime (time)
    time_t    time;
{
    struct tm	  	*parts;
    static char	  	buf[128];

    parts = localtime(&time);
    (void)strftime(buf, sizeof buf, "%k:%M:%S %b %d, %Y", parts);
    return(buf);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_PrintType --
 *	Print out a type field giving only those attributes the user can
 *	set.
 *
 * Results:
 *
 * Side Effects:
 *
 *-----------------------------------------------------------------------
 */
void
Targ_PrintType (type)
    register int    type;
{
    register int    tbit;

#ifdef __STDC__
#define PRINTBIT(attr)	case CONCAT(OP_,attr): printf("." #attr " "); break
#define PRINTDBIT(attr) case CONCAT(OP_,attr): if (DEBUG(TARG)) printf("." #attr " "); break
#else
#define PRINTBIT(attr) 	case CONCAT(OP_,attr): printf(".attr "); break
#define PRINTDBIT(attr)	case CONCAT(OP_,attr): if (DEBUG(TARG)) printf(".attr "); break
#endif /* __STDC__ */

    type &= ~OP_OPMASK;

    while (type) {
	tbit = 1 << (ffs(type) - 1);
	type &= ~tbit;

	switch(tbit) {
	    PRINTBIT(OPTIONAL);
	    PRINTBIT(USE);
	    PRINTBIT(EXEC);
	    PRINTBIT(IGNORE);
	    PRINTBIT(PRECIOUS);
	    PRINTBIT(SILENT);
	    PRINTBIT(MAKE);
	    PRINTBIT(JOIN);
	    PRINTBIT(INVISIBLE);
	    PRINTBIT(NOTMAIN);
	    PRINTDBIT(LIB);
	    /*XXX: MEMBER is defined, so CONCAT(OP_,MEMBER) gives OP_"%" */
	    case OP_MEMBER: if (DEBUG(TARG)) printf(".MEMBER "); break;
	    PRINTDBIT(ARCHV);
	}
    }
}

/*-
 *-----------------------------------------------------------------------
 * TargPrintNode --
 *	print the contents of a node
 *-----------------------------------------------------------------------
 */
static int
TargPrintNode (gnp, passp)
    ClientData   gnp;
    ClientData	 passp;
{
    GNode         *gn = (GNode *) gnp;
    int	    	  pass = *(int *) passp;
    if (!OP_NOP(gn->type)) {
	printf("#\n");
	if (gn == mainTarg) {
	    printf("# *** MAIN TARGET ***\n");
	}
	if (pass == 2) {
	    if (gn->unmade) {
		printf("# %d unmade children\n", gn->unmade);
	    } else {
		printf("# No unmade children\n");
	    }
	    if (! (gn->type & (OP_JOIN|OP_USE|OP_USEBEFORE|OP_EXEC))) {
		if (gn->mtime != 0) {
		    printf("# last modified %s: %s\n",
			      Targ_FmtTime(gn->mtime),
			      (gn->made == UNMADE ? "unmade" :
			       (gn->made == MADE ? "made" :
				(gn->made == UPTODATE ? "up-to-date" :
				 "error when made"))));
		} else if (gn->made != UNMADE) {
		    printf("# non-existent (maybe): %s\n",
			      (gn->made == MADE ? "made" :
			       (gn->made == UPTODATE ? "up-to-date" :
				(gn->made == ERROR ? "error when made" :
				 "aborted"))));
		} else {
		    printf("# unmade\n");
		}
	    }
	    if (!Lst_IsEmpty (gn->iParents)) {
		printf("# implicit parents: ");
		Lst_ForEach (gn->iParents, TargPrintName, (ClientData)0);
		fputc ('\n', stdout);
	    }
	}
	if (!Lst_IsEmpty (gn->parents)) {
	    printf("# parents: ");
	    Lst_ForEach (gn->parents, TargPrintName, (ClientData)0);
	    fputc ('\n', stdout);
	}

	printf("%-16s", gn->name);
	switch (gn->type & OP_OPMASK) {
	    case OP_DEPENDS:
		printf(": "); break;
	    case OP_FORCE:
		printf("! "); break;
	    case OP_DOUBLEDEP:
		printf(":: "); break;
	}
	Targ_PrintType (gn->type);
	Lst_ForEach (gn->children, TargPrintName, (ClientData)0);
	fputc ('\n', stdout);
	Lst_ForEach (gn->commands, Targ_PrintCmd, (ClientData)0);
	printf("\n\n");
	if (gn->type & OP_DOUBLEDEP) {
	    Lst_ForEach (gn->cohorts, TargPrintNode, (ClientData)&pass);
	}
    }
    return (0);
}

/*-
 *-----------------------------------------------------------------------
 * TargPrintOnlySrc --
 *	Print only those targets that are just a source.
 *
 * Results:
 *	0.
 *
 * Side Effects:
 *	The name of each file is printed preceded by #\t
 *
 *-----------------------------------------------------------------------
 */
static int
TargPrintOnlySrc(gnp, dummy)
    ClientData 	  gnp;
    ClientData 	  dummy;
{
    GNode   	  *gn = (GNode *) gnp;
    if (OP_NOP(gn->type))
	printf("#\t%s [%s]\n", gn->name, gn->path ? gn->path : gn->name);

    return (dummy ? 0 : 0);
}

/*-
 *-----------------------------------------------------------------------
 * Targ_PrintGraph --
 *	print the entire graph. heh heh
 *
 * Results:
 *	none
 *
 * Side Effects:
 *	lots o' output
 *-----------------------------------------------------------------------
 */
void
Targ_PrintGraph (pass)
    int	    pass; 	/* Which pass this is. 1 => no processing
			 * 2 => processing done */
{
    printf("#*** Input graph:\n");
    Lst_ForEach (allTargets, TargPrintNode, (ClientData)&pass);
    printf("\n\n");
    printf("#\n#   Files that are only sources:\n");
    Lst_ForEach (allTargets, TargPrintOnlySrc, (ClientData) 0);
    printf("#*** Global Variables:\n");
    Var_Dump (VAR_GLOBAL);
    printf("#*** Command-line Variables:\n");
    Var_Dump (VAR_CMD);
    printf("\n");
    Dir_PrintDirectories();
    printf("\n");
    Suff_PrintAll();
}

static int
TargPropagateCohort (cgnp, pgnp)
    ClientData   cgnp;
    ClientData   pgnp;
{
    GNode	  *cgn = (GNode *) cgnp;
    GNode	  *pgn = (GNode *) pgnp;

    cgn->type |= pgn->type & ~OP_OPMASK;
    return (0);
}

static int
TargPropagateNode (gnp, junk)
    ClientData   gnp;
    ClientData   junk;
{
    GNode	  *gn = (GNode *) gnp;
    if (gn->type & OP_DOUBLEDEP)
	Lst_ForEach (gn->cohorts, TargPropagateCohort, gnp);
    return (0);
}

void
Targ_Propagate ()
{
    Lst_ForEach (allTargets, TargPropagateNode, (ClientData)0);
}
