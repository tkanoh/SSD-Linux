/*	$ssdlinux: main.c,v 1.1.1.1 2002/05/02 13:37:10 kanoh Exp $	*/
/*	$NetBSD: main.c,v 1.81 2001/12/11 20:50:58 tv Exp $	*/

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
static char rcsid[] = "$NetBSD: main.c,v 1.81 2001/12/11 20:50:58 tv Exp $";
#else
#include <sys/cdefs.h>
/*
#ifndef lint
__COPYRIGHT("@(#) Copyright (c) 1988, 1989, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif */ /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)main.c	8.3 (Berkeley) 3/19/94";
/*
#else
__RCSID("$NetBSD: main.c,v 1.81 2001/12/11 20:50:58 tv Exp $");
*/
#endif
#endif /* not lint */
#endif

/*-
 * main.c --
 *	The main file for this entire program. Exit routines etc
 *	reside here.
 *
 * Utility functions defined in this file:
 *	Main_ParseArgLine	Takes a line of arguments, breaks them and
 *				treats them as if they were given when first
 *				invoked. Used by the parse module to implement
 *				the .MFLAGS target.
 *
 *	Error			Print a tagged error message. The global
 *				MAKE variable must have been defined. This
 *				takes a format string and two optional
 *				arguments for it.
 *
 *	Fatal			Print an error message and exit. Also takes
 *				a format string and two arguments.
 *
 *	Punt			Aborts all jobs and exits with a message. Also
 *				takes a format string and two arguments.
 *
 *	Finish			Finish things up by printing the number of
 *				errors which occurred, as passed to it, and
 *				exiting.
 */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <sys/stat.h>
#ifndef MAKE_BOOTSTRAP
#include <sys/utsname.h>
#endif
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "make.h"
#include "hash.h"
#include "dir.h"
#include "job.h"
#include "pathnames.h"
#include "trace.h"

#ifdef USE_IOVEC
#include <sys/uio.h>
#endif

#ifndef	DEFMAXLOCAL
#define	DEFMAXLOCAL DEFMAXJOBS
#endif	/* DEFMAXLOCAL */

Lst			create;		/* Targets to be made */
time_t			now;		/* Time at start of make */
GNode			*DEFAULT;	/* .DEFAULT node */
Boolean			allPrecious;	/* .PRECIOUS given on line by itself */

static Boolean		noBuiltins;	/* -r flag */
static Lst		makefiles;	/* ordered list of makefiles to read */
static Boolean		printVars;	/* print value of one or more vars */
static Lst		variables;	/* list of variables to print */
int			maxJobs;	/* -j argument */
static int		maxLocal;	/* -L argument */
Boolean			compatMake;	/* -B argument */
Boolean			debug;		/* -d flag */
Boolean			noExecute;	/* -n flag */
Boolean			noRecursiveExecute;	/* -N flag */
Boolean			keepgoing;	/* -k flag */
Boolean			queryFlag;	/* -q flag */
Boolean			touchFlag;	/* -t flag */
Boolean			usePipes;	/* !-P flag */
Boolean			ignoreErrors;	/* -i flag */
Boolean			beSilent;	/* -s flag */
Boolean			oldVars;	/* variable substitution style */
Boolean			checkEnvFirst;	/* -e flag */
Boolean			parseWarnFatal;	/* -W flag */
Boolean			jobServer; 	/* -J flag */
static Boolean		jobsRunning;	/* TRUE if the jobs might be running */
static const char *	tracefile;
static char *		Check_Cwd_av __P((int, char **, int));
static void		MainParseArgs __P((int, char **));
static int		ReadMakefile __P((ClientData, ClientData));
static void		usage __P((void));

static char curdir[MAXPATHLEN + 1];	/* startup directory */
static char objdir[MAXPATHLEN + 1];	/* where we chdir'ed to */
char *progname;				/* the program name */

Boolean forceJobs = FALSE;

extern Lst parseIncPath;

/*-
 * MainParseArgs --
 *	Parse a given argument vector. Called from main() and from
 *	Main_ParseArgLine() when the .MAKEFLAGS target is used.
 *
 *	XXX: Deal with command line overriding .MAKEFLAGS in makefile
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Various global and local flags will be set depending on the flags
 *	given
 */
static void
MainParseArgs(argc, argv)
	int argc;
	char **argv;
{
	char *p;
	int c;

	optind = 1;	/* since we're called more than once */
#ifdef REMOTE
# define OPTFLAGS "BD:I:J:L:NPST:V:Wd:ef:ij:km:nqrst"
#else
# define OPTFLAGS "BD:I:J:NPST:V:Wd:ef:ij:km:nqrst"
#endif
rearg:	while((c = getopt(argc, argv, OPTFLAGS)) != -1) {
		switch(c) {
		case 'D':
			Var_Set(optarg, "1", VAR_GLOBAL, 0);
			Var_Append(MAKEFLAGS, "-D", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'I':
			Parse_AddIncludeDir(optarg);
			Var_Append(MAKEFLAGS, "-I", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'J':
			if (sscanf(optarg, "%d,%d", &job_pipe[0], &job_pipe[1]) != 2) {
			    /* backslash to avoid trigraph ??) */
			    (void)fprintf(stderr,
				"%s: internal error -- J option malformed (%s?\?)\n",
				progname, optarg);
				usage();
			}
			if ((fcntl(job_pipe[0], F_GETFD, 0) < 0) ||
			    (fcntl(job_pipe[1], F_GETFD, 0) < 0)) {
#if 0
			    (void)fprintf(stderr,
				"%s: warning -- J descriptors were closed!\n",
				progname);
#endif
			    job_pipe[0] = -1;
			    job_pipe[1] = -1;
			    compatMake = TRUE;
			} else {
			    Var_Append(MAKEFLAGS, "-J", VAR_GLOBAL);
			    Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			    jobServer = TRUE;
			}
			break;
		case 'V':
			printVars = TRUE;
			(void)Lst_AtEnd(variables, (ClientData)optarg);
			Var_Append(MAKEFLAGS, "-V", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'B':
			compatMake = TRUE;
			break;
#ifdef REMOTE
		case 'L':
			maxLocal = strtol(optarg, &p, 0);
			if (*p != '\0' || maxLocal < 1) {
			    (void) fprintf(stderr, "%s: illegal argument to -L -- must be positive integer!\n",
				progname);
			    exit(1);
			}
			Var_Append(MAKEFLAGS, "-L", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
#endif
		case 'N':
			noExecute = TRUE;
			noRecursiveExecute = TRUE;
			Var_Append(MAKEFLAGS, "-N", VAR_GLOBAL);
			break;
		case 'P':
			usePipes = FALSE;
			Var_Append(MAKEFLAGS, "-P", VAR_GLOBAL);
			break;
		case 'S':
			keepgoing = FALSE;
			Var_Append(MAKEFLAGS, "-S", VAR_GLOBAL);
			break;
		case 'T':
			tracefile = estrdup(optarg);
			Var_Append(MAKEFLAGS, "-T", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'W':
			parseWarnFatal = TRUE;
			break;
		case 'd': {
			char *modules = optarg;

			for (; *modules; ++modules)
				switch (*modules) {
				case 'A':
					debug = ~0;
					break;
				case 'a':
					debug |= DEBUG_ARCH;
					break;
				case 'c':
					debug |= DEBUG_COND;
					break;
				case 'd':
					debug |= DEBUG_DIR;
					break;
				case 'f':
					debug |= DEBUG_FOR;
					break;
				case 'g':
					if (modules[1] == '1') {
						debug |= DEBUG_GRAPH1;
						++modules;
					}
					else if (modules[1] == '2') {
						debug |= DEBUG_GRAPH2;
						++modules;
					}
					break;
				case 'j':
					debug |= DEBUG_JOB;
					break;
				case 'm':
					debug |= DEBUG_MAKE;
					break;
				case 's':
					debug |= DEBUG_SUFF;
					break;
				case 't':
					debug |= DEBUG_TARG;
					break;
				case 'v':
					debug |= DEBUG_VAR;
					break;
				case 'x':
					debug |= DEBUG_SHELL;
					break;
				default:
					(void)fprintf(stderr,
				"%s: illegal argument to d option -- %c\n",
					    progname, *modules);
					usage();
				}
			Var_Append(MAKEFLAGS, "-d", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		}
		case 'e':
			checkEnvFirst = TRUE;
			Var_Append(MAKEFLAGS, "-e", VAR_GLOBAL);
			break;
		case 'f':
			(void)Lst_AtEnd(makefiles, (ClientData)optarg);
			break;
		case 'i':
			ignoreErrors = TRUE;
			Var_Append(MAKEFLAGS, "-i", VAR_GLOBAL);
			break;
		case 'j':
			forceJobs = TRUE;
			maxJobs = strtol(optarg, &p, 0);
			if (*p != '\0' || maxJobs < 1) {
				(void) fprintf(stderr, "%s: illegal argument to -j -- must be positive integer!\n",
				    progname);
				exit(1);
			}
#ifndef REMOTE
			maxLocal = maxJobs;
#endif
			Var_Append(MAKEFLAGS, "-j", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'k':
			keepgoing = TRUE;
			Var_Append(MAKEFLAGS, "-k", VAR_GLOBAL);
			break;
		case 'm':
			(void) Dir_AddDir(sysIncPath, optarg);
			Var_Append(MAKEFLAGS, "-m", VAR_GLOBAL);
			Var_Append(MAKEFLAGS, optarg, VAR_GLOBAL);
			break;
		case 'n':
			noExecute = TRUE;
			Var_Append(MAKEFLAGS, "-n", VAR_GLOBAL);
			break;
		case 'q':
			queryFlag = TRUE;
			/* Kind of nonsensical, wot? */
			Var_Append(MAKEFLAGS, "-q", VAR_GLOBAL);
			break;
		case 'r':
			noBuiltins = TRUE;
			Var_Append(MAKEFLAGS, "-r", VAR_GLOBAL);
			break;
		case 's':
			beSilent = TRUE;
			Var_Append(MAKEFLAGS, "-s", VAR_GLOBAL);
			break;
		case 't':
			touchFlag = TRUE;
			Var_Append(MAKEFLAGS, "-t", VAR_GLOBAL);
			break;
		default:
		case '?':
			usage();
		}
	}

	oldVars = TRUE;

	/*
	 * See if the rest of the arguments are variable assignments and
	 * perform them if so. Else take them to be targets and stuff them
	 * on the end of the "create" list.
	 */
	for (argv += optind, argc -= optind; *argv; ++argv, --argc)
		if (Parse_IsVar(*argv)) {
			Parse_DoVar(*argv, VAR_CMD);
		} else {
			if (!**argv)
				Punt("illegal (null) argument.");
			if (**argv == '-') {
				if ((*argv)[1])
					optind = 0;     /* -flag... */
				else
					optind = 1;     /* - */
				goto rearg;
			}
			(void)Lst_AtEnd(create, (ClientData)estrdup(*argv));
		}
}

/*-
 * Main_ParseArgLine --
 *  	Used by the parse module when a .MFLAGS or .MAKEFLAGS target
 *	is encountered and by main() when reading the .MAKEFLAGS envariable.
 *	Takes a line of arguments and breaks it into its
 * 	component words and passes those words and the number of them to the
 *	MainParseArgs function.
 *	The line should have all its leading whitespace removed.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	Only those that come from the various arguments.
 */
void
Main_ParseArgLine(line)
	char *line;			/* Line to fracture */
{
	char **argv;			/* Manufactured argument vector */
	int argc;			/* Number of arguments in argv */
	char *args;			/* Space used by the args */
	char *buf, *p1;
	char *argv0 = Var_Value(".MAKE", VAR_GLOBAL, &p1);
	size_t len;

	if (line == NULL)
		return;
	for (; *line == ' '; ++line)
		continue;
	if (!*line)
		return;

	buf = emalloc(len = strlen(line) + strlen(argv0) + 2);
	(void)snprintf(buf, len, "%s %s", argv0, line);
	if (p1)
		free(p1);

	argv = brk_string(buf, &argc, TRUE, &args);
	free(buf);
	MainParseArgs(argc, argv);

	free(args);
	free(argv);
}

Boolean
Main_SetObjdir(path)
	const char *path;
{
	struct stat sb;
	char *p = NULL;
	char buf[MAXPATHLEN + 1];
	Boolean rc = FALSE;

	/* expand variable substitutions */
	if (strchr(path, '$') != 0) {
		snprintf(buf, MAXPATHLEN, "%s", path);
		path = p = Var_Subst(NULL, buf, VAR_GLOBAL, 0);
	}

	if (path[0] != '/') {
		snprintf(buf, MAXPATHLEN, "%s/%s", curdir, path);
		path = buf;
	}

	/* look for the directory and try to chdir there */
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		if (chdir(path)) {
			(void)fprintf(stderr, "make warning: %s: %s.\n",
				      path, strerror(errno));
		} else {
			strncpy(objdir, path, MAXPATHLEN);
			Var_Set(".OBJDIR", objdir, VAR_GLOBAL, 0);
			setenv("PWD", objdir, 1);
			Dir_InitDot();
			rc = TRUE;
		}
	}

	if (p)
		free(p);
	return rc;
}


/*-
 * main --
 *	The main function, for obvious reasons. Initializes variables
 *	and a few modules, then parses the arguments give it in the
 *	environment and on the command line. Reads the system makefile
 *	followed by either Makefile, makefile or the file given by the
 *	-f argument. Sets the .MAKEFLAGS PMake variable based on all the
 *	flags it has received by then uses either the Make or the Compat
 *	module to create the initial list of targets.
 *
 * Results:
 *	If -q was given, exits -1 if anything was out-of-date. Else it exits
 *	0.
 *
 * Side Effects:
 *	The program exits when done. Targets are created. etc. etc. etc.
 */
int
main(argc, argv)
	int argc;
	char **argv;
{
	Lst targs;	/* target nodes to create -- passed to Make_Init */
	Boolean outOfDate = TRUE; 	/* FALSE if all targets up to date */
	struct stat sb, sa;
	char *p1, *path, *pwd;
	char mdpath[MAXPATHLEN];
    	char *machine = getenv("MACHINE");
	char *machine_arch = getenv("MACHINE_ARCH");
	char *syspath = getenv("MAKESYSPATH");
	Lst sysMkPath;			/* Path of sys.mk */
	char *cp = NULL, *start;
					/* avoid faults on read-only strings */
	static char defsyspath[] = _PATH_DEFSYSPATH;
	
	if ((progname = strrchr(argv[0], '/')) != NULL)
		progname++;
	else
		progname = argv[0];
#ifdef RLIMIT_NOFILE
	/*
	 * get rid of resource limit on file descriptors
	 */
	{
		struct rlimit rl;
		if (getrlimit(RLIMIT_NOFILE, &rl) != -1 &&
		    rl.rlim_cur != rl.rlim_max) {
			rl.rlim_cur = rl.rlim_max;
			(void) setrlimit(RLIMIT_NOFILE, &rl);
		}
	}
#endif
	/*
	 * Find where we are and take care of PWD for the automounter...
	 * All this code is so that we know where we are when we start up
	 * on a different machine with pmake.
	 */
	if (getcwd(curdir, MAXPATHLEN) == NULL) {
		(void)fprintf(stderr, "%s: %s.\n", progname, strerror(errno));
		exit(2);
	}

	if (stat(curdir, &sa) == -1) {
	    (void)fprintf(stderr, "%s: %s: %s.\n",
		 progname, curdir, strerror(errno));
	    exit(2);
	}

	/*
	 * Overriding getcwd() with $PWD totally breaks MAKEOBJDIRPREFIX
	 * since the value of curdir can very depending on how we got
	 * here.  Ie sitting at a shell prompt (shell that provides $PWD)
	 * or via subdir.mk in which case its likely a shell which does
	 * not provide it.
	 * So, to stop it breaking this case only, we ignore PWD if
	 * MAKEOBJDIRPREFIX is set or MAKEOBJDIR contains a transform.
	 */
	if ((pwd = getenv("PWD")) != NULL && getenv("MAKEOBJDIRPREFIX") == NULL) {
		const char *makeobjdir = getenv("MAKEOBJDIR");

		if (makeobjdir == NULL || !strchr(makeobjdir, '$')) {
			if (stat(pwd, &sb) == 0 && sa.st_ino == sb.st_ino &&
			    sa.st_dev == sb.st_dev)
				(void) strncpy(curdir, pwd, MAXPATHLEN);
		}
	}

	/*
	 * Get the name of this type of MACHINE from utsname
	 * so we can share an executable for similar machines.
	 * (i.e. m68k: amiga hp300, mac68k, sun3, ...)
	 *
	 * Note that both MACHINE and MACHINE_ARCH are decided at
	 * run-time.
	 */
	if (!machine) {
#ifndef MAKE_BOOTSTRAP
	    struct utsname utsname;

	    if (uname(&utsname) == -1) {
		(void)fprintf(stderr, "%s: uname failed (%s).\n", progname,
		    strerror(errno));
		exit(2);
	    }
	    machine = utsname.machine;
#else
#ifdef MAKE_MACHINE
	    machine = MAKE_MACHINE;
#else
	    machine = "unknown";
#endif
#endif
	}

	if (!machine_arch) {
#ifndef MACHINE_ARCH
#ifdef MAKE_MACHINE_ARCH
            machine_arch = MAKE_MACHINE_ARCH;
#else
	    machine_arch = "unknown";
#endif
#else
	    machine_arch = MACHINE_ARCH;
#endif
	}

	/*
	 * Just in case MAKEOBJDIR wants us to do something tricky.
	 */
	Var_Init();		/* Initialize the lists of variables for
				 * parsing arguments */
	Var_Set(".CURDIR", curdir, VAR_GLOBAL, 0);
	Var_Set("MACHINE", machine, VAR_GLOBAL, 0);
	Var_Set("MACHINE_ARCH", machine_arch, VAR_GLOBAL, 0);
#ifdef MAKE_VERSION
	Var_Set("MAKE_VERSION", MAKE_VERSION, VAR_GLOBAL, 0);
#endif
	Var_Set(".newline", "\n", VAR_GLOBAL, 0); /* handy for :@ loops */

	/*
	 * Find the .OBJDIR.  If MAKEOBJDIRPREFIX, or failing that,
	 * MAKEOBJDIR is set in the environment, try only that value
	 * and fall back to .CURDIR if it does not exist.
	 *
	 * Otherwise, try _PATH_OBJDIR.MACHINE, _PATH_OBJDIR, and
	 * finally _PATH_OBJDIRPREFIX`pwd`, in that order.  If none
	 * of these paths exist, just use .CURDIR.
	 */
	Dir_Init(curdir);
	(void) Main_SetObjdir(curdir);

	if ((path = getenv("MAKEOBJDIRPREFIX")) != NULL) {
		(void) snprintf(mdpath, MAXPATHLEN, "%s%s", path, curdir);
		(void) Main_SetObjdir(mdpath);
	} else if ((path = getenv("MAKEOBJDIR")) != NULL) {
		(void) Main_SetObjdir(path);
	} else {
		(void) snprintf(mdpath, MAXPATHLEN, "%s.%s", _PATH_OBJDIR, machine);
		if (!Main_SetObjdir(mdpath) && !Main_SetObjdir(_PATH_OBJDIR)) {
			(void) snprintf(mdpath, MAXPATHLEN, "%s%s", 
					_PATH_OBJDIRPREFIX, curdir);
			(void) Main_SetObjdir(mdpath);
		}
	}

	create = Lst_Init(FALSE);
	makefiles = Lst_Init(FALSE);
	printVars = FALSE;
	variables = Lst_Init(FALSE);
	beSilent = FALSE;		/* Print commands as executed */
	ignoreErrors = FALSE;		/* Pay attention to non-zero returns */
	noExecute = FALSE;		/* Execute all commands */
	noRecursiveExecute = FALSE;	/* Execute all .MAKE targets */
	keepgoing = FALSE;		/* Stop on error */
	allPrecious = FALSE;		/* Remove targets when interrupted */
	queryFlag = FALSE;		/* This is not just a check-run */
	noBuiltins = FALSE;		/* Read the built-in rules */
	touchFlag = FALSE;		/* Actually update targets */
	usePipes = TRUE;		/* Catch child output in pipes */
	debug = 0;			/* No debug verbosity, please. */
	jobsRunning = FALSE;

	maxLocal = DEFMAXLOCAL;		/* Set default local max concurrency */
#ifdef REMOTE
	maxJobs = DEFMAXJOBS;		/* Set default max concurrency */
#else
	maxJobs = maxLocal;
#endif
	compatMake = FALSE;		/* No compat mode */


	/*
	 * Initialize the parsing, directory and variable modules to prepare
	 * for the reading of inclusion paths and variable settings on the
	 * command line
	 */

	/*
	 * Initialize various variables.
	 *	MAKE also gets this name, for compatibility
	 *	.MAKEFLAGS gets set to the empty string just in case.
	 *	MFLAGS also gets initialized empty, for compatibility.
	 */
	Parse_Init();
	Var_Set("MAKE", argv[0], VAR_GLOBAL, 0);
	Var_Set(".MAKE", argv[0], VAR_GLOBAL, 0);
	Var_Set(MAKEFLAGS, "", VAR_GLOBAL, 0);
	Var_Set(MAKEOVERRIDES, "", VAR_GLOBAL, 0);
	Var_Set("MFLAGS", "", VAR_GLOBAL, 0);
	Var_Set(".ALLTARGETS", "", VAR_GLOBAL, 0);

	/*
	 * First snag any flags out of the MAKE environment variable.
	 * (Note this is *not* MAKEFLAGS since /bin/make uses that and it's
	 * in a different format).
	 */
#ifdef POSIX
	Main_ParseArgLine(getenv("MAKEFLAGS"));
#else
	Main_ParseArgLine(getenv("MAKE"));
#endif

	MainParseArgs(argc, argv);

	/*
	 * Be compatible if user did not specify -j and did not explicitly
	 * turned compatibility on
	 */
	if (!compatMake && !forceJobs) {
		compatMake = TRUE;
	}
	
	/*
	 * Initialize archive, target and suffix modules in preparation for
	 * parsing the makefile(s)
	 */
	Arch_Init();
	Targ_Init();
	Suff_Init();
	Trace_Init(tracefile);

	DEFAULT = NILGNODE;
	(void)time(&now);

	Trace_Log(MAKESTART, NULL);
	
	/*
	 * Set up the .TARGETS variable to contain the list of targets to be
	 * created. If none specified, make the variable empty -- the parser
	 * will fill the thing in with the default or .MAIN target.
	 */
	if (!Lst_IsEmpty(create)) {
		LstNode ln;

		for (ln = Lst_First(create); ln != NILLNODE;
		    ln = Lst_Succ(ln)) {
			char *name = (char *)Lst_Datum(ln);

			Var_Append(".TARGETS", name, VAR_GLOBAL);
		}
	} else
		Var_Set(".TARGETS", "", VAR_GLOBAL, 0);


	/*
	 * If no user-supplied system path was given (through the -m option)
	 * add the directories from the DEFSYSPATH (more than one may be given
	 * as dir1:...:dirn) to the system include path.
	 */
	if (syspath == NULL || *syspath == '\0')
		syspath = defsyspath;
	else
		syspath = strdup(syspath);

	for (start = syspath; *start != '\0'; start = cp) {
		for (cp = start; *cp != '\0' && *cp != ':'; cp++)
			continue;
		if (*cp == '\0') {
			(void) Dir_AddDir(defIncPath, start);
		} else {
			*cp++ = '\0';
			(void) Dir_AddDir(defIncPath, start);
		}
	}
	if (syspath != defsyspath)
		free(syspath);

	/*
	 * Read in the built-in rules first, followed by the specified
	 * makefile, if it was (makefile != (char *) NULL), or the default
	 * Makefile and makefile, in that order, if it wasn't.
	 */
	if (!noBuiltins) {
		LstNode ln;

		sysMkPath = Lst_Init (FALSE);
		Dir_Expand(_PATH_DEFSYSMK,
			   Lst_IsEmpty(sysIncPath) ? defIncPath : sysIncPath,
			   sysMkPath);
		if (Lst_IsEmpty(sysMkPath))
			Fatal("%s: no system rules (%s).", progname,
			    _PATH_DEFSYSMK);
		ln = Lst_Find(sysMkPath, (ClientData)NULL, ReadMakefile);
		if (ln != NILLNODE)
			Fatal("%s: cannot open %s.", progname,
			    (char *)Lst_Datum(ln));
	}

	if (!Lst_IsEmpty(makefiles)) {
		LstNode ln;

		ln = Lst_Find(makefiles, (ClientData)NULL, ReadMakefile);
		if (ln != NILLNODE)
			Fatal("%s: cannot open %s.", progname, 
			    (char *)Lst_Datum(ln));
	} else if (!ReadMakefile("makefile", NULL))
		(void)ReadMakefile("Makefile", NULL);

	(void)ReadMakefile(".depend", NULL);

	Var_Append("MFLAGS", Var_Value(MAKEFLAGS, VAR_GLOBAL, &p1), VAR_GLOBAL);
	if (p1)
	    free(p1);

	if (!jobServer && !compatMake)
	    Job_ServerStart(maxJobs);
	if (DEBUG(JOB))
	    printf("job_pipe %d %d, maxjobs %d maxlocal %d compat %d\n", job_pipe[0], job_pipe[1], maxJobs,
	           maxLocal, compatMake);

	Main_ExportMAKEFLAGS(TRUE);	/* initial export */

	Check_Cwd_av(0, NULL, 0);	/* initialize it */
	

	/*
	 * For compatibility, look at the directories in the VPATH variable
	 * and add them to the search path, if the variable is defined. The
	 * variable's value is in the same format as the PATH envariable, i.e.
	 * <directory>:<directory>:<directory>...
	 */
	if (Var_Exists("VPATH", VAR_CMD)) {
		char *vpath, *path, *cp, savec;
		/*
		 * GCC stores string constants in read-only memory, but
		 * Var_Subst will want to write this thing, so store it
		 * in an array
		 */
		static char VPATH[] = "${VPATH}";

		vpath = Var_Subst(NULL, VPATH, VAR_CMD, FALSE);
		path = vpath;
		do {
			/* skip to end of directory */
			for (cp = path; *cp != ':' && *cp != '\0'; cp++)
				continue;
			/* Save terminator character so know when to stop */
			savec = *cp;
			*cp = '\0';
			/* Add directory to search path */
			(void) Dir_AddDir(dirSearchPath, path);
			*cp = savec;
			path = cp + 1;
		} while (savec == ':');
		(void)free((Address)vpath);
	}

	/*
	 * Now that all search paths have been read for suffixes et al, it's
	 * time to add the default search path to their lists...
	 */
	Suff_DoPaths();

	/*
	 * Propagate attributes through :: dependency lists.
	 */
	Targ_Propagate();

	/* print the initial graph, if the user requested it */
	if (DEBUG(GRAPH1))
		Targ_PrintGraph(1);

	/* print the values of any variables requested by the user */
	if (printVars) {
		LstNode ln;

		for (ln = Lst_First(variables); ln != NILLNODE;
		    ln = Lst_Succ(ln)) {
			char *value = Var_Value((char *)Lst_Datum(ln),
					  VAR_GLOBAL, &p1);

			printf("%s\n", value ? value : "");
			if (p1)
				free(p1);
		}
	}

	/*
	 * Have now read the entire graph and need to make a list of targets
	 * to create. If none was given on the command line, we consult the
	 * parsing module to find the main target(s) to create.
	 */
	if (Lst_IsEmpty(create))
		targs = Parse_MainName();
	else
		targs = Targ_FindList(create, TARG_CREATE);

	if (!compatMake && !printVars) {
		/*
		 * Initialize job module before traversing the graph, now that
		 * any .BEGIN and .END targets have been read.  This is done
		 * only if the -q flag wasn't given (to prevent the .BEGIN from
		 * being executed should it exist).
		 */
		if (!queryFlag) {
			if (maxLocal == -1)
				maxLocal = maxJobs;
			Job_Init(maxJobs, maxLocal);
			jobsRunning = TRUE;
		}

		/* Traverse the graph, checking on all the targets */
		outOfDate = Make_Run(targs);
	} else if (!printVars) {
		/*
		 * Compat_Init will take care of creating all the targets as
		 * well as initializing the module.
		 */
		Compat_Run(targs);
	}

#ifdef CLEANUP
	Lst_Destroy(targs, NOFREE);
	Lst_Destroy(variables, NOFREE);
	Lst_Destroy(makefiles, NOFREE);
	Lst_Destroy(create, (void (*) __P((ClientData))) free);
#endif

	/* print the graph now it's been processed if the user requested it */
	if (DEBUG(GRAPH2))
		Targ_PrintGraph(2);

	Trace_Log(MAKEEND, 0);

	Suff_End();
        Targ_End();
	Arch_End();
	Var_End();
	Parse_End();
	Dir_End();
	Job_End();
	Trace_End();

	if (queryFlag && outOfDate)
		return(1);
	else
		return(0);
}

/*-
 * ReadMakefile  --
 *	Open and parse the given makefile.
 *
 * Results:
 *	TRUE if ok. FALSE if couldn't open file.
 *
 * Side Effects:
 *	lots
 */
static Boolean
ReadMakefile(p, q)
	ClientData p, q;
{
	char *fname = p;		/* makefile to read */
	FILE *stream;
	size_t len = MAXPATHLEN;
	char *name, *path = emalloc(len);
	int setMAKEFILE;

	if (!strcmp(fname, "-")) {
		Parse_File("(stdin)", stdin);
		Var_Set("MAKEFILE", "", VAR_GLOBAL, 0);
	} else {
		setMAKEFILE = strcmp(fname, ".depend");

		/* if we've chdir'd, rebuild the path name */
		if (strcmp(curdir, objdir) && *fname != '/') {
			size_t plen = strlen(curdir) + strlen(fname) + 2;
			if (len < plen)
				path = erealloc(path, len = 2 * plen);
			
			(void)snprintf(path, len, "%s/%s", curdir, fname);
			if ((stream = fopen(path, "r")) != NULL) {
				fname = path;
				goto found;
			}
		} else if ((stream = fopen(fname, "r")) != NULL)
			goto found;
		/* look in -I and system include directories. */
		name = Dir_FindFile(fname, parseIncPath);
		if (!name)
			name = Dir_FindFile(fname,
				Lst_IsEmpty(sysIncPath) ? defIncPath : sysIncPath);
		if (!name || !(stream = fopen(name, "r"))) {
			free(path);
			return(FALSE);
		}
		fname = name;
		/*
		 * set the MAKEFILE variable desired by System V fans -- the
		 * placement of the setting here means it gets set to the last
		 * makefile specified, as it is set by SysV make.
		 */
found:
		if (setMAKEFILE)
			Var_Set("MAKEFILE", fname, VAR_GLOBAL, 0);
		Parse_File(fname, stream);
		(void)fclose(stream);
	}
	free(path);
	return(TRUE);
}


/*
 * If MAKEOBJDIRPREFIX is in use, make ends up not in .CURDIR
 * in situations that would not arrise with ./obj (links or not).
 * This tends to break things like:
 *
 * build:
 * 	${MAKE} includes
 *
 * This function spots when ${.MAKE:T} or ${.MAKE} is a command (as
 * opposed to an argument) in a command line and if so returns
 * ${.CURDIR} so caller can chdir() so that the assumptions made by
 * the Makefile hold true.
 *
 * If ${.MAKE} does not contain any '/', then ${.MAKE:T} is skipped.
 *
 * The chdir() only happens in the child process, and does nothing if
 * MAKEOBJDIRPREFIX and MAKEOBJDIR are not in the environment so it
 * should not break anything.  Also if NOCHECKMAKECHDIR is set we
 * do nothing - to ensure historic semantics can be retained.
 */
static int  Check_Cwd_Off = 0;

static char *
Check_Cwd_av(ac, av, copy)
     int ac;
     char **av;
     int copy;
{
    static char *make[4];
    static char *curdir = NULL;
    char *cp, **mp;
    int is_cmd, next_cmd;
    int i;
    int n;

    if (Check_Cwd_Off)
	return NULL;
    
    if (make[0] == NULL) {
	if (Var_Exists("NOCHECKMAKECHDIR", VAR_GLOBAL)) {
	    Check_Cwd_Off = 1;
	    return NULL;
	}
	    
        make[1] = Var_Value(".MAKE", VAR_GLOBAL, &cp);
        if ((make[0] = strrchr(make[1], '/')) == NULL) {
            make[0] = make[1];
            make[1] = NULL;
        } else
            ++make[0];
        make[2] = NULL;
        curdir = Var_Value(".CURDIR", VAR_GLOBAL, &cp);
    }
    if (ac == 0 || av == NULL)
        return NULL;			/* initialization only */

    if (getenv("MAKEOBJDIR") == NULL &&
        getenv("MAKEOBJDIRPREFIX") == NULL)
        return NULL;

    
    next_cmd = 1;
    for (i = 0; i < ac; ++i) {
	is_cmd = next_cmd;

	n = strlen(av[i]);
	cp = &(av[i])[n - 1];
	if (strspn(av[i], "|&;") == n) {
	    next_cmd = 1;
	    continue;
	} else if (*cp == ';' || *cp == '&' || *cp == '|' || *cp == ')') {
	    next_cmd = 1;
	    if (copy) {
		do {
		    *cp-- = '\0';
		} while (*cp == ';' || *cp == '&' || *cp == '|' ||
			 *cp == ')' || *cp == '}') ;
	    } else {
		/*
		 * XXX this should not happen.
		 */
		fprintf(stderr, "WARNING: raw arg ends in shell meta '%s'\n",
			av[i]);
	    }
	} else
	    next_cmd = 0;

	cp = av[i];
	if (*cp == ';' || *cp == '&' || *cp == '|')
	    is_cmd = 1;
	
#ifdef check_cwd_debug
	fprintf(stderr, "av[%d] == %s '%s'",
		i, (is_cmd) ? "cmd" : "arg", av[i]);
#endif
	if (is_cmd != 0) {
	    if (*cp == '(' || *cp == '{' ||
		*cp == ';' || *cp == '&' || *cp == '|') {
		do {
		    ++cp;
		} while (*cp == '(' || *cp == '{' ||
			 *cp == ';' || *cp == '&' || *cp == '|');
		if (*cp == '\0') {
		    next_cmd = 1;
		    continue;
		}
	    }
	    if (strcmp(cp, "cd") == 0 || strcmp(cp, "chdir") == 0) {
#ifdef check_cwd_debug
		fprintf(stderr, " == cd, done.\n");
#endif
		return NULL;
	    }
	    for (mp = make; *mp != NULL; ++mp) {
		n = strlen(*mp);
		if (strcmp(cp, *mp) == 0) {
#ifdef check_cwd_debug
		    fprintf(stderr, " %s == '%s', chdir(%s)\n",
			    cp, *mp, curdir);
#endif
		    return curdir;
		}
	    }
	}
#ifdef check_cwd_debug
	fprintf(stderr, "\n");
#endif
    }
    return NULL;
}

char *
Check_Cwd_Cmd(cmd)
     char *cmd;
{
    char *cp, *bp, **av;
    int ac;

    if (Check_Cwd_Off)
	return NULL;
    
    if (cmd) {
	av = brk_string(cmd, &ac, TRUE, &bp);
#ifdef check_cwd_debug
	fprintf(stderr, "splitting: '%s' -> %d words\n",
		cmd, ac);
#endif
    } else {
	ac = 0;
	av = NULL;
	bp = NULL;
    }
    cp = Check_Cwd_av(ac, av, 1);
    if (bp) {
	free(av);
	free(bp);
    }
    return cp;
}

void
Check_Cwd(argv)
    char **argv;
{
    char *cp;
    int ac;
    
    if (Check_Cwd_Off)
	return;
    
    for (ac = 0; argv[ac] != NULL; ++ac)
	/* NOTHING */;
    if (ac == 3 && *argv[1] == '-') {
	cp =  Check_Cwd_Cmd(argv[2]);
    } else {
	cp = Check_Cwd_av(ac, argv, 0);
    }
    if (cp) {
	chdir(cp);
    }
}

/*-
 * Cmd_Exec --
 *	Execute the command in cmd, and return the output of that command
 *	in a string.
 *
 * Results:
 *	A string containing the output of the command, or the empty string
 *	If err is not NULL, it contains the reason for the command failure
 *
 * Side Effects:
 *	The string must be freed by the caller.
 */
char *
Cmd_Exec(cmd, err)
    char *cmd;
    char **err;
{
    char	*args[4];   	/* Args for invoking the shell */
    int 	fds[2];	    	/* Pipe streams */
    int 	cpid;	    	/* Child PID */
    int 	pid;	    	/* PID from wait() */
    char	*res;		/* result */
    int		status;		/* command exit status */
    Buffer	buf;		/* buffer to store the result */
    char	*cp;
    int		cc;


    *err = NULL;

    /*
     * Set up arguments for shell
     */
    args[0] = "sh";
    args[1] = "-c";
    args[2] = cmd;
    args[3] = NULL;

    /*
     * Open a pipe for fetching its output
     */
    if (pipe(fds) == -1) {
	*err = "Couldn't create pipe for \"%s\"";
	goto bad;
    }

    /*
     * Fork
     */
    switch (cpid = vfork()) {
    case 0:
	/*
	 * Close input side of pipe
	 */
	(void) close(fds[0]);

	/*
	 * Duplicate the output stream to the shell's output, then
	 * shut the extra thing down. Note we don't fetch the error
	 * stream...why not? Why?
	 */
	(void) dup2(fds[1], 1);
	(void) close(fds[1]);

	(void) execv("/bin/sh", args);
	_exit(1);
	/*NOTREACHED*/

    case -1:
	*err = "Couldn't exec \"%s\"";
	goto bad;

    default:
	/*
	 * No need for the writing half
	 */
	(void) close(fds[1]);

	buf = Buf_Init (MAKE_BSIZE);

	do {
	    char   result[BUFSIZ];
	    cc = read(fds[0], result, sizeof(result));
	    if (cc > 0)
		Buf_AddBytes(buf, cc, (Byte *) result);
	}
	while (cc > 0 || (cc == -1 && errno == EINTR));

	/*
	 * Close the input side of the pipe.
	 */
	(void) close(fds[0]);

	/*
	 * Wait for the process to exit.
	 */
	while(((pid = wait(&status)) != cpid) && (pid >= 0))
	    continue;

	res = (char *)Buf_GetAll (buf, &cc);
	Buf_Destroy (buf, FALSE);

	if (cc == 0)
	    *err = "Couldn't read shell's output for \"%s\"";

	if (status)
	    *err = "\"%s\" returned non-zero status";

	/*
	 * Null-terminate the result, convert newlines to spaces and
	 * install it in the variable.
	 */
	res[cc] = '\0';
	cp = &res[cc];

	if (cc > 0 && *--cp == '\n') {
	    /*
	     * A final newline is just stripped
	     */
	    *cp-- = '\0';
	}
	while (cp >= res) {
	    if (*cp == '\n') {
		*cp = ' ';
	    }
	    cp--;
	}
	break;
    }
    return res;
bad:
    res = emalloc(1);
    *res = '\0';
    return res;
}

/*-
 * Error --
 *	Print an error message given its format.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The message is printed.
 */
/* VARARGS */
void
#ifdef __STDC__
Error(char *fmt, ...)
#else
Error(va_alist)
	va_dcl
#endif
{
	va_list ap;
#ifdef __STDC__
	va_start(ap, fmt);
#else
	char *fmt;

	va_start(ap);
	fmt = va_arg(ap, char *);
#endif
	fprintf(stderr, "%s: ", progname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);
}

/*-
 * Fatal --
 *	Produce a Fatal error message. If jobs are running, waits for them
 *	to finish.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The program exits
 */
/* VARARGS */
void
#ifdef __STDC__
Fatal(char *fmt, ...)
#else
Fatal(va_alist)
	va_dcl
#endif
{
	va_list ap;
#ifdef __STDC__
	va_start(ap, fmt);
#else
	char *fmt;

	va_start(ap);
	fmt = va_arg(ap, char *);
#endif
	if (jobsRunning)
		Job_Wait();
	Job_TokenFlush();

	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);

	PrintOnError(NULL);

	if (DEBUG(GRAPH2))
		Targ_PrintGraph(2);
	Trace_Log(MAKEERROR, 0);
	exit(2);		/* Not 1 so -q can distinguish error */
}

/*
 * Punt --
 *	Major exception once jobs are being created. Kills all jobs, prints
 *	a message and exits.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	All children are killed indiscriminately and the program Lib_Exits
 */
/* VARARGS */
void
#ifdef __STDC__
Punt(char *fmt, ...)
#else
Punt(va_alist)
	va_dcl
#endif
{
	va_list ap;
#ifdef __STDC__
	va_start(ap, fmt);
#else
	char *fmt;

	va_start(ap);
	fmt = va_arg(ap, char *);
#endif

	(void)fprintf(stderr, "%s: ", progname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	(void)fflush(stderr);

	PrintOnError(NULL);

	DieHorribly();
}

/*-
 * DieHorribly --
 *	Exit without giving a message.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	A big one...
 */
void
DieHorribly()
{
	if (jobsRunning)
		Job_AbortAll();
	if (DEBUG(GRAPH2))
		Targ_PrintGraph(2);
	Trace_Log(MAKEERROR, 0);
	exit(2);		/* Not 1, so -q can distinguish error */
}

/*
 * Finish --
 *	Called when aborting due to errors in child shell to signal
 *	abnormal exit.
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The program exits
 */
void
Finish(errors)
	int errors;	/* number of errors encountered in Make_Make */
{
	Fatal("%d error%s", errors, errors == 1 ? "" : "s");
}

/*
 * emalloc --
 *	malloc, but die on error.
 */
void *
emalloc(len)
	size_t len;
{
	void *p;

	if ((p = malloc(len)) == NULL)
		enomem();
	return(p);
}

/*
 * estrdup --
 *	strdup, but die on error.
 */
char *
estrdup(str)
	const char *str;
{
	char *p;

	if ((p = strdup(str)) == NULL)
		enomem();
	return(p);
}

/*
 * erealloc --
 *	realloc, but die on error.
 */
void *
erealloc(ptr, size)
	void *ptr;
	size_t size;
{
	if ((ptr = realloc(ptr, size)) == NULL)
		enomem();
	return(ptr);
}

/*
 * enomem --
 *	die when out of memory.
 */
void
enomem()
{
	(void)fprintf(stderr, "%s: %s.\n", progname, strerror(errno));
	exit(2);
}

/*
 * enunlink --
 *	Remove a file carefully, avoiding directories.
 */
int
eunlink(file)
	const char *file;
{
	struct stat st;

	if (lstat(file, &st) == -1)
		return -1;

	if (S_ISDIR(st.st_mode)) {
		errno = EISDIR;
		return -1;
	}
	return unlink(file);
}

/*
 * execError --
 *	Print why exec failed, avoiding stdio.
 */
void
execError(av)
	const char *av;
{
#ifdef USE_IOVEC
	int i = 0;
	struct iovec iov[6];
#define IOADD(s) \
	(void)(iov[i].iov_base = (s), \
	    iov[i].iov_len = strlen(iov[i].iov_base), \
	    i++)
#else
#define	IOADD (void)write(2, s, strlen(s))
#endif

	IOADD(progname);
	IOADD(": Exec of `");
	IOADD((char *)av);
	IOADD("' failed (");
	IOADD(strerror(errno));
	IOADD(")\n");

#ifdef USE_IOVEC
	(void)writev(2, iov, 6);
#endif
}

/*
 * usage --
 *	exit with usage message
 */
static void
usage()
{
	(void)fprintf(stderr,
"Usage: %s [-Beiknqrst] [-D variable] [-d flags] [-f makefile ]\n\
            [-I directory] [-j max_jobs] [-m directory] [-V variable]\n\
            [variable=value] [target ...]\n", progname);
	exit(2);
}


int
PrintAddr(a, b)
    ClientData a;
    ClientData b;
{
    printf("%lx ", (unsigned long) a);
    return b ? 0 : 0;
}



void
PrintOnError(s)
    char *s;
{
    char tmp[64];
	
    if (s)
	    printf("%s", s);
	
    printf("\n%s: stopped in %s\n", progname, curdir);
    strncpy(tmp, "${MAKE_PRINT_VAR_ON_ERROR:@v@$v='${$v}'\n@}",
	    sizeof(tmp) - 1);
    s = Var_Subst(NULL, tmp, VAR_GLOBAL, 0);
    if (s && *s)
	printf("%s", s);
}

void
Main_ExportMAKEFLAGS(first)
     Boolean first;
{
    static int once = 1;
    char tmp[64];
    char *s;

    if (once != first)
	return;
    once = 0;
    
    strncpy(tmp, "${.MAKEFLAGS} ${.MAKEOVERRIDES:O:u:@v@$v=${$v:Q}@}",
	    sizeof(tmp));
    s = Var_Subst(NULL, tmp, VAR_CMD, 0);
    if (s && *s) {
#ifdef POSIX
	setenv("MAKEFLAGS", s, 1);
#else
	setenv("MAKE", s, 1);
#endif
    }
}
