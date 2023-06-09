/*	$ssdlinux: tip.c,v 1.1 2004/11/12 15:22:13 kanoh Exp $	*/
/*	$NetBSD: tip.c,v 1.28 2004/11/04 07:29:09 dsl Exp $	*/

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
__COPYRIGHT("@(#) Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)tip.c	8.1 (Berkeley) 6/6/93";
#endif
__RCSID("$NetBSD: tip.c,v 1.28 2004/11/04 07:29:09 dsl Exp $");
#endif /* not lint */
#endif

/*
 * tip - UNIX link to other systems
 *  tip [-v] [-speed] system-name
 * or
 *  cu phone-number [-s speed] [-l line] [-a acu]
 */
#include "tip.h"
#include "pathnames.h"

/*
 * Baud rate mapping table
 */
int rates[] = {
	0, 50, 75, 110, 134, 150, 200, 300, 600,
	1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200, -1
};

int	escape __P((void));
int	main __P((int, char **));
void	intprompt __P((int));
void	tipin __P((void));

char	PNbuf[256];			/* This limits the size of a number */

static char path_phones[] = _PATH_PHONES;

int
main(argc, argv)
	int argc;
	char *argv[];
{
	char *System = NULL;
	int i;
	char *p;
	const char *q;
	char sbuf[12];
	int fcarg;

	gid = getgid();
	egid = getegid();
	uid = getuid();
	euid = geteuid();
	if (equal(basename(argv[0]), "cu")) {
		cumode = 1;
		cumain(argc, argv);
		goto cucommon;
	}

	if (argc > 4) {
		fprintf(stderr, "usage: tip [-v] [-speed] [system-name]\n");
		exit(1);
	}
	if (!isatty(0)) {
		fprintf(stderr, "tip: must be interactive\n");
		exit(1);
	}

	for (; argc > 1; argv++, argc--) {
		if (argv[1][0] != '-')
			System = argv[1];
		else switch (argv[1][1]) {

		case 'v':
			vflag++;
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			BR = atoi(&argv[1][1]);
			break;

		default:
			fprintf(stderr, "tip: %s, unknown option\n", argv[1]);
			break;
		}
	}

	if (System == NULL)
		goto notnumber;
	if (isalpha((unsigned char)*System))
		goto notnumber;
	/*
	 * System name is really a phone number...
	 * Copy the number then stomp on the original (in case the number
	 *	is private, we don't want 'ps' or 'w' to find it).
	 */
	if (strlen(System) > sizeof PNbuf - 1) {
		fprintf(stderr, "tip: phone number too long (max = %d bytes)\n",
			(int)sizeof(PNbuf) - 1);
		exit(1);
	}
	(void)strlcpy(PNbuf, System, sizeof(PNbuf));
	for (p = System; *p; p++)
		*p = '\0';
	PN = PNbuf;
	(void)snprintf(sbuf, sizeof sbuf, "tip%d", (int)BR);
	System = sbuf;

notnumber:
	(void)signal(SIGINT, cleanup);
	(void)signal(SIGQUIT, cleanup);
	(void)signal(SIGHUP, cleanup);
	(void)signal(SIGTERM, cleanup);

	if ((i = hunt(System)) == 0) {
		printf("all ports busy\n");
		exit(3);
	}
	if (i == -1) {
		printf("link down\n");
		(void)uu_unlock(uucplock);
		exit(3);
	}
	setbuf(stdout, NULL);
	loginit();

	/*
	 * Now that we have the logfile and the ACU open
	 *  return to the real uid and gid.  These things will
	 *  be closed on exit.  Swap real and effective uid's
	 *  so we can get the original permissions back
	 *  for removing the uucp lock.
	 */
	user_uid();

	/*
	 * Kludge, their's no easy way to get the initialization
	 *   in the right order, so force it here
	 */
	if ((PH = getenv("PHONES")) == NULL)
		PH = path_phones;
	vinit();				/* init variables */
	setparity("even");			/* set the parity table */
	if ((i = speed(number(value(BAUDRATE)))) == 0) {
		printf("tip: bad baud rate %d\n", (int)number(value(BAUDRATE)));
		daemon_uid();
		(void)uu_unlock(uucplock);
		exit(3);
	}

	/*
	 * Hardwired connections require the
	 *  line speed set before they make any transmissions
	 *  (this is particularly true of things like a DF03-AC)
	 */
	if (HW)
		ttysetup(i);
	if ((q = connect()) != NULL) {
		printf("\07%s\n[EOT]\n", q);
		daemon_uid();
		(void)uu_unlock(uucplock);
		exit(1);
	}
	if (!HW)
		ttysetup(i);

	/*
	 * Direct connections with no carrier require using O_NONBLOCK on
	 * open, but we don't want to keep O_NONBLOCK after open because it
	 * will cause busy waits.
	 */
	if (DC &&
	    ((fcarg = fcntl(FD, F_GETFL, 0)) < 0 ||
	     fcntl(FD, F_SETFL, fcarg & ~O_NONBLOCK) < 0)) {
		printf("tip: can't clear O_NONBLOCK: %s", strerror (errno));
		daemon_uid();
		(void)uu_unlock(uucplock);
		exit(1);
	}
		
cucommon:
	/*
	 * From here down the code is shared with
	 * the "cu" version of tip.
	 */

	tcgetattr(0, &defterm);
	term = defterm;
	term.c_lflag &= ~(ICANON|IEXTEN|ECHO);
	term.c_iflag &= ~(INPCK|ICRNL);
	term.c_oflag &= ~OPOST;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	defchars = term;
#if 0
	term.c_cc[VINTR] = term.c_cc[VQUIT] = term.c_cc[VSUSP] =
		term.c_cc[VDSUSP] = term.c_cc[VDISCARD] = 
	 	term.c_cc[VLNEXT] = _POSIX_VDISABLE;
#else
	term.c_cc[VINTR] = term.c_cc[VQUIT] = term.c_cc[VSUSP] =
		term.c_cc[VDISCARD] = 
	 	term.c_cc[VLNEXT] = _POSIX_VDISABLE;
#endif
	raw();

	pipe(fildes); pipe(repdes);
	(void)signal(SIGALRM, alrmtimeout);

	/*
	 * Everything's set up now:
	 *	connection established (hardwired or dialup)
	 *	line conditioned (baud rate, mode, etc.)
	 *	internal data structures (variables)
	 * so, fork one process for local side and one for remote.
	 */
	printf("%s", cumode ? "Connected\r\n" : "\07connected\r\n");
	switch (pid = fork()) {
	default:
		tipin();
		break;
	case 0:
		tipout();
		break;
	case -1:
		err(1, "can't fork");
	}
	/*NOTREACHED*/
	exit(0);	/* XXX: pacify gcc */
}

void
cleanup(dummy)
	int dummy;
{

	daemon_uid();
	(void)uu_unlock(uucplock);
	if (odisc)
		ioctl(0, TIOCSETD, (char *)&odisc);
	exit(0);
}

/*
 * Muck with user ID's.  We are setuid to the owner of the lock
 * directory when we start.  user_uid() reverses real and effective
 * ID's after startup, to run with the user's permissions.
 * daemon_uid() switches back to the privileged uid for unlocking.
 * Finally, to avoid running a shell with the wrong real uid,
 * shell_uid() sets real and effective uid's to the user's real ID.
 */
static int uidswapped;

void
user_uid()
{

	if (uidswapped == 0) {
		seteuid(uid);
		uidswapped = 1;
	}
}

void
daemon_uid()
{

	if (uidswapped) {
		seteuid(euid);
		uidswapped = 0;
	}
}

void
shell_uid()
{

	seteuid(uid);
}

/*
 * put the controlling keyboard into raw mode
 */
void
raw()
{

	tcsetattr(0, TCSADRAIN, &term);
}


/*
 * return keyboard to normal mode
 */
void
unraw()
{

	tcsetattr(0, TCSADRAIN, &defterm);
}

static	jmp_buf promptbuf;

/*
 * Print string ``s'', then read a string
 *  in from the terminal.  Handles signals & allows use of
 *  normal erase and kill characters.
 */
int
prompt(s, p, l)
	const char *s;
	char *p;
	size_t l;
{
	int c;
	char *b = p;
	sig_t oint, oquit;

#if __GNUC__		/* XXX: pacify gcc */
	(void)&p;
#endif

	stoprompt = 0;
	oint = signal(SIGINT, intprompt);
	oquit = signal(SIGQUIT, SIG_IGN);
	unraw();
	printf("%s", s);
	if (setjmp(promptbuf) == 0)
		while ((c = getchar()) != -1 && (*p = c) != '\n' &&
		    b + l > p)
			p++;
	*p = '\0';

	raw();
	(void)signal(SIGINT, oint);
	(void)signal(SIGQUIT, oquit);
	return (stoprompt || p == b);
}

/*
 * Interrupt service routine during prompting
 */
void
intprompt(dummy)
	int dummy;
{

	(void)signal(SIGINT, SIG_IGN);
	stoprompt = 1;
	printf("\r\n");
	longjmp(promptbuf, 1);
}

/*
 * ****TIPIN   TIPIN****
 */
void
tipin()
{
	char gch, bol = 1;

	/*
	 * Kinda klugey here...
	 *   check for scripting being turned on from the .tiprc file,
	 *   but be careful about just using setscript(), as we may
	 *   send a SIGEMT before tipout has a chance to set up catching
	 *   it; so wait a second, then setscript()
	 */
	if (boolean(value(SCRIPT))) {
		sleep(1);
		setscript();
	}

	while (1) {
		gch = getchar()&STRIP_PAR;
		if ((gch == character(value(ESCAPE))) && bol) {
			if (!(gch = escape()))
				continue;
		} else if (!cumode && 
		    gch && gch == character(value(RAISECHAR))) {
			setboolean(value(RAISE), !boolean(value(RAISE)));
			continue;
		} else if (gch == '\r') {
			bol = 1;
			xpwrite(FD, &gch, 1);
			if (boolean(value(HALFDUPLEX)))
				printf("\r\n");
			continue;
		} else if (!cumode && gch && gch == character(value(FORCE)))
			gch = getchar()&STRIP_PAR;
		bol = any(gch, value(EOL));
		if (boolean(value(RAISE)) && islower((unsigned char)gch))
			gch = toupper((unsigned char)gch);
		xpwrite(FD, &gch, 1);
		if (boolean(value(HALFDUPLEX)))
			printf("%c", gch);
	}
}

/*
 * Escape handler --
 *  called on recognition of ``escapec'' at the beginning of a line
 */
int
escape()
{
	char gch;
	esctable_t *p;
	char c = character(value(ESCAPE));

	gch = (getchar()&STRIP_PAR);
	for (p = etable; p->e_char; p++)
		if (p->e_char == gch) {
			if ((p->e_flags&PRIV) && uid)
				continue;
			printf("%s", ctrl(c));
			(*p->e_func)(gch);
			return (0);
		}
	/* ESCAPE ESCAPE forces ESCAPE */
	if (c != gch)
		xpwrite(FD, &c, 1);
	return (gch);
}

int
speed(n)
	int n;
{
	int *p;

	for (p = rates; *p != -1;  p++)
		if (*p == n)
			return n;
	return 0;
}

int
any(c, p)
	char c;
	const char *p;
{

	while (p && *p)
		if (*p++ == c)
			return (1);
	return (0);
}

char *
interp(s)
	const char *s;
{
	static char buf[256];
	char *p = buf, c;
	const char *q;

	while ((c = *s++) != 0 && buf + sizeof buf - p > 2) {
		for (q = "\nn\rr\tt\ff\033E\bb"; *q; q++)
			if (*q++ == c) {
				*p++ = '\\'; *p++ = *q;
				goto next;
			}
		if (c < 040) {
			*p++ = '^'; *p++ = c + 'A'-1;
		} else if (c == 0177) {
			*p++ = '^'; *p++ = '?';
		} else
			*p++ = c;
	next:
		;
	}
	*p = '\0';
	return (buf);
}

char *
ctrl(c)
	char c;
{
	static char s[3];

	if (c < 040 || c == 0177) {
		s[0] = '^';
		s[1] = c == 0177 ? '?' : c+'A'-1;
		s[2] = '\0';
	} else {
		s[0] = c;
		s[1] = '\0';
	}
	return (s);
}

/*
 * Help command
 */
void
help(c)
	char c;
{
	esctable_t *p;

	printf("%c\r\n", c);
	for (p = etable; p->e_char; p++) {
		if ((p->e_flags&PRIV) && uid)
			continue;
		printf("%2s", ctrl(character(value(ESCAPE))));
		printf("%-2s %c   %s\r\n", ctrl(p->e_char),
			p->e_flags&EXP ? '*': ' ', p->e_help);
	}
}

/*
 * Set up the "remote" tty's state
 */
void
ttysetup(spd)
	int spd;
{
	struct termios	cntrl;

	tcgetattr(FD, &cntrl);
	cfsetospeed(&cntrl, spd);
	cfsetispeed(&cntrl, spd);
	cntrl.c_cflag &= ~(CSIZE|PARENB);
	cntrl.c_cflag |= CS8;
	if (DC)
		cntrl.c_cflag |= CLOCAL;
	cntrl.c_iflag &= ~(ISTRIP|ICRNL);
	cntrl.c_oflag &= ~OPOST;
	cntrl.c_lflag &= ~(ICANON|ISIG|IEXTEN|ECHO);
	cntrl.c_cc[VMIN] = 1;
	cntrl.c_cc[VTIME] = 0;
	if (boolean(value(TAND)))
		cntrl.c_iflag |= IXOFF;
	tcsetattr(FD, TCSAFLUSH, &cntrl);
}

static char partab[0200];

/*
 * Do a write to the remote machine with the correct parity.
 * We are doing 8 bit wide output, so we just generate a character
 * with the right parity and output it.
 */
void
xpwrite(fd, buf, n)
	int fd;
	char *buf;
	int n;
{
	int i;
	char *bp;

	bp = buf;
	if (bits8 == 0)
		for (i = 0; i < n; i++) {
			*bp = partab[(*bp) & 0177];
			bp++;
		}
	if (write(fd, buf, n) < 0) {
		if (errno == EIO)
			tipabort("Lost carrier.");
		/* this is questionable */
		perror("write");
	}
}

/*
 * Build a parity table with appropriate high-order bit.
 */
void
setparity(defparity)
	const char *defparity;
{
	int i, flip, clr, set;
	const char *parity;
	static char *curpar;

	if (value(PARITY) == NULL || (value(PARITY))[0] == '\0') {
		if (curpar != NULL)
			free(curpar);
		value(PARITY) = curpar = strdup(defparity);
	}
	parity = value(PARITY);
	if (equal(parity, "none")) {
		bits8 = 1;
		return;
	}
	bits8 = 0;
	flip = 0;
	clr = 0377;
	set = 0;
	if (equal(parity, "odd"))
		flip = 0200;			/* reverse bit 7 */
	else if (equal(parity, "zero"))
		clr = 0177;			/* turn off bit 7 */
	else if (equal(parity, "one"))
		set = 0200;			/* turn on bit 7 */
	else if (!equal(parity, "even")) {
		(void) fprintf(stderr, "%s: unknown parity value\r\n", parity);
		(void) fflush(stderr);
	}
	for (i = 0; i < 0200; i++)
		partab[i] = ((evenpartab[i] ^ flip) | set) & clr;
}
