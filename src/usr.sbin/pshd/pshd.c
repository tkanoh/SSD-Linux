/*	$ssdlinux: pshd.c,v 1.4 2004/07/29 09:32:33 todoroki Exp $	*/
/*
 * Push SW deamon
 */
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <asm/ioctls.h>
#ifdef HAVE_PUSHSW_OBS2XX_H
#include <asm/pushsw_obs2xx.h>
#else
#include <asm/pushsw.h>
#endif
#include <signal.h>

void donothing(int i);
void die(int i);

int
main(int argc, char *argv[])
{
	int fd, rv, arg;
	int pid;

#ifdef CONFIG_OPENBLOCKS266
	int fdups;
	int opt_c;
	int opt_idx;
	int upscheck = 1;
	int upswaittime = 5;

	static struct option long_options[] = {
		{"noupswatch", 0, 0, 0},
		{"upswaittime", 1, 0, 0}};

	while((opt_c = getopt_long (argc, argv, "", long_options, &opt_idx)) != -1) {
		switch(opt_c) {
		case 0:
			if (opt_idx == 0) {
#ifdef  DEBUG
				fprintf(stderr,"--noupscheck\n");
#endif
				upscheck = 0;
			} else {
				if (optarg) {
					sscanf(optarg,"%d",&upswaittime);
#ifdef  DEBUG
					fprintf(stderr,"--upswaittime %d\n",upswaittime);	
#endif
					if ((upswaittime < 1) || (upswaittime > 10)) {
						upswaittime = 5;
					}
				}
			}
		}
	}
#endif
	if (getuid()) {
		fprintf(stderr, "must run super user\n");
		return 1;
	}
	if ((pid = fork())) {
		/* parent */
#ifdef  DEBUG
		fprintf(stderr,"parent\n");
#endif
		return 0;
	} else {
		/* child */
#ifdef  DEBUG
		fprintf(stderr,"child\n");
#endif
		signal(SIGHUP,donothing);
		signal(SIGINT,die);
		signal(SIGQUIT,die);
		signal(SIGILL,die);
		signal(SIGTRAP,die);
		signal(SIGABRT,die);
		signal(SIGIOT,die);
		signal(SIGBUS,die);
		signal(SIGFPE,die);
//		signal(SIGKILL,die);
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
		if ((fd = open("/dev/pushsw", O_RDONLY | O_NONBLOCK)) < 0) {
			perror("open");
			exit(-1);
		}
#ifdef CONFIG_OPENBLOCKS266
		if (upscheck == 1) {
			if ((fdups = open("/dev/ttyS1", O_RDONLY | O_NONBLOCK)) < 0) {
				perror("UPS open");
			} else {
				rv = ioctl(fdups, UPSIOSTART , &arg);
				if (rv) {
#ifdef DEBUG
					fprintf(stderr,"UPSIOSTART ttyS0\n");
#endif
					close(fdups);
					if ((fdups = open("/dev/ttyS0", O_RDONLY | O_NONBLOCK)) < 0) {
						perror("UPS open");
					} else {
					rv = ioctl(fdups, UPSIOSTART , &arg);
					}
				}
#ifdef DEBUG
				fprintf(stderr,"UPSIOSTART %d\n",rv);
#endif
				rv = ioctl(fdups, UPSIOTIME, upswaittime);
#ifdef DEBUG
				fprintf(stderr,"UPSIOTIME %d\n",rv);
#endif
				close(fdups);
			} 
			
		}
#endif
		rv = ioctl(fd, PSWIOC_WAITPUSH, &arg);
		if (rv < 0) {
			perror("blocked");
			exit(-1);
		}
		/* At this point, push sw has been pushed! shutdown system */
		execl("/sbin/shutdown", "shutdown", "-h", "now", NULL);
		return 0;
	}
}

void donothing(int i) {
#ifdef DEBUG
	fprintf(stderr,"donothing %d\n",i);
#endif
}
void die(int i) {
#ifdef DEBUG
	fprintf(stderr,"die %d\n",i);
#endif
#ifdef CONFIG_OPENBLOCKS266
	int     fdups, arg, rv;
	if ((fdups = open("/dev/ttyS1", O_RDONLY | O_NONBLOCK)) < 0) {
		perror("UPS open");
	} else {
		rv = ioctl(fdups, UPSIOSTOP, &arg);
#ifdef DEBUG
		fprintf(stderr,"UPSIOSTOP %d\n",rv);
#endif
		close(fdups);
	}
#endif
	exit(0);
}

