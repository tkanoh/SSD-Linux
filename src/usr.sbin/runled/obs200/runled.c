/*	$ssdlinux: runled.c,v 1.6 2003/11/04 06:10:20 todoroki Exp $	*/
/*
 * runled -- LED daemon for OpenBlockS/OpenBlockSS
 * Copyright (C) 2002 Masaki WAKABAYASHI <masaki@quox.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include <stddef.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/ioctl.h>
#include <signal.h>

/* definitions for ioctl() */
#define SEGLED_IOCTL_BASE 'S'
#define SLIOC_SETSEG _IOR(SEGLED_IOCTL_BASE, 2, int)

/* definitions of command-name, special file path, ... */
#define COMMAND_NAME     "runled"
#define DEFAULT_PATH     "/dev/segled"
#define DEFAULT_PATTERN  "0808889010109088"
#define DEFAULT_INTERVAL 150
#define PID_FILE "/var/run/segled.pid"

static void show_led(int, const unsigned int*, int, int);
static unsigned int str2num(const char*);
static void string2pattern(const char*, unsigned int*, int);
static void transpattern_obss2obs(unsigned int*, int);
void donothing(int i){}
void die(int i){exit(0);}

void show_led(int fd, const unsigned int* pattern, int size, int interval)
{
	int i = 0;
	interval *= 1000;
	while (1) {
		unsigned int v = pattern[i];
		ioctl(fd, SLIOC_SETSEG, v);
		i++;
		if (i == size) i = 0;
		usleep(interval);
	}
	/* never reached here */
}

unsigned int str2num(const char* s)
{
	int v = 0;
	while (1) {
		int c, n;
		c = *s;
		if (!isdigit(c)) break;
		n = v * 10 + (c - '0');
		if (n <= v) {
			v = UINT_MAX;
			break;
		} else {
			v = n;
		}
		s++;
	}
	return v;
}

void string2pattern(const char* s, unsigned int* d, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		int c;
		unsigned int h, l;
		c = *s;
		if (isdigit(c)) {
			h = c - '0';
		} else if (isxdigit(c)) {
			h = c - (isupper(c) ? ('A' - 10) : ('a' - 10));
		} else {
			h = 0;
		}
		s++;
		c = *s;
		if (isdigit(c)) {
			l = c - '0';
		} else if (isxdigit(c)) {
			l = c - (isupper(c) ? ('A' - 10) : ('a' - 10));
		} else {
			l = 0;
		}
		s++;
		*d = ((h << 4) | l);
		d++;
	}
}

void transpattern_obss2obs(unsigned int* s, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		unsigned int old, new;
		old = s[i];
		new = 0;
		if ((old & 0x01) != 0) new |= 0x00020000;
		if ((old & 0x02) != 0) new |= 0x00010000;
		if ((old & 0x04) != 0) new |= 0x00008000;
		if ((old & 0x08) != 0) new |= 0x00004000;
		if ((old & 0x10) != 0) new |= 0x00000001;
		if ((old & 0x20) != 0) new |= 0x00000002;
		if ((old & 0x40) != 0) new |= 0x00000004;
		if ((old & 0x80) != 0) new |= 0x00000008;
		s[i] = new;
	}
}

int main(int argc, const char* const* argv)
{
	const char default_pattern_string[] = DEFAULT_PATTERN;
	const char* path = DEFAULT_PATH;
	const char* pattern_string = default_pattern_string;
	int interval = DEFAULT_INTERVAL, nofork_flag = 0, obs_flag = 0;
	unsigned int* pattern;
	int size;
	int fd,fd2;
	pid_t pid;
	char tmpbuf[100];

	/* check command-line argument(s) */
	if (argc > 1) {
		size_t i = 1;
		while (argv[i] != NULL) {
			unsigned char c;
			if (*argv[i] != '-') continue;
			c = *(argv[i] + 1);
			switch (c) {
			case 'f':
				nofork_flag = 1;
				break;
			case 'i':
				{
					int tmp = str2num(argv[i] + 2);
					if (tmp > 0 && tmp < 3600000) interval = tmp;
				}
				break;
			case 'o':
				obs_flag = 1;
				break;
			case 'p':
				if (*(argv[i] + 2) != '\0') pattern_string = argv[i] + 2;
				break;
			default:
				fprintf(stderr, COMMAND_NAME ": unknown option `-%c'.\n", c);
				exit(1);
			}
			i++;
		}
	}

	/* allocate memory for pattern buffer */
	size = strlen(pattern_string) / 2;
	pattern = (unsigned int*)malloc(size * sizeof(*pattern));
	if (pattern == NULL) {
		fprintf(stderr, COMMAND_NAME ": malloc: %s.\n", strerror(errno));
		exit(1);
	}

	/* set pattern table from string */
	string2pattern(pattern_string, pattern, size);
	if (obs_flag) transpattern_obss2obs(pattern, size);

	/* open special file */
	fd = open(path, O_CREAT|O_WRONLY|O_TRUNC);
	if (fd < 0) {
		fprintf(stderr, COMMAND_NAME ": open `%s': %s.\n",
				path, strerror(errno));
		free(pattern);
		exit(1);
	}

	/* close needless fds */
	close(0);
	close(1);

	/* exec main service */
	if (nofork_flag) {
		if ((fd2 = open(PID_FILE, O_CREAT|O_WRONLY|O_TRUNC)) < 0) {
			free(pattern);
			perror("open");
			close(fd);
			exit(-1);
		}
		sprintf(tmpbuf, "%d\n", pid);
		if (write(fd2, tmpbuf, strlen(tmpbuf)) != strlen(tmpbuf)) {
			free(pattern);
			perror("write");
			close(fd);
			close(fd2);
			exit(-2);
		}
		close(fd2);
		/* no fork model: show patterns to LED */
		show_led(fd, pattern, size, interval);
		/* never reached here */
	} else {
		/* fork model */
		pid = fork();
		if (pid == 0) {
			/* child process: same as no fork model */
			signal(SIGHUP,donothing);
			signal(SIGINT,die);
			signal(SIGQUIT,die);
			signal(SIGILL,die);
			signal(SIGTRAP,die);
			signal(SIGABRT,die);
			signal(SIGIOT,die);
			signal(SIGBUS,die);
			signal(SIGFPE,die);
			signal(SIGKILL,die);
			signal(SIGUSR1,die);
			signal(SIGSEGV,die);
			signal(SIGUSR2,die);
			signal(SIGPIPE,die);
			signal(SIGALRM,die);
			signal(SIGTERM,die);
			signal(SIGSTKFLT,die);
			signal(SIGCHLD,die);
			signal(SIGCONT,die);
			signal(SIGSTOP,die);
			signal(SIGTSTP,die);
			signal(SIGTTIN,die);
			signal(SIGTTOU,die);
			signal(SIGURG,die);
			signal(SIGXCPU,die);
			signal(SIGXFSZ,die);
			signal(SIGVTALRM,die);
			signal(SIGPROF,die);
			signal(SIGWINCH,die);
			signal(SIGIO,die);
			signal(SIGPWR,die);
			signal(SIGSYS,die);
			show_led(fd, pattern, size, interval);
			/* never reached here */
		} else if (pid > 0) {
			/* parent process: exit only */
			if ((fd2 = open(PID_FILE, O_CREAT|O_WRONLY|O_TRUNC)) < 0) {
				free(pattern);
				perror("open");
				close(fd);
				exit(-1);
			}
			sprintf(tmpbuf, "%d\n", pid);
			if (write(fd2, tmpbuf, strlen(tmpbuf)) != strlen(tmpbuf)) {
				free(pattern);
				perror("write");
				close(fd);
				close(fd2);
				exit(-2);
			}
			close(fd2);
		} else {
			/* fork error, die */
			fprintf(stderr, COMMAND_NAME ": %s.\n", strerror(errno));
			free(pattern);
			close(fd);
			exit(1);
		}
	}
	free(pattern);
	close(fd);

	return 0;
}
