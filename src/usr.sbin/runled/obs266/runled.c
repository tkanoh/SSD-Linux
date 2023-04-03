/*	$ssdlinux: runled.c,v 1.3 2003/03/27 14:18:12 todoroki Exp $	*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define PID_FILE "/var/run/segled.pid"

#define LED_SPEED	(500*1000)

void donothing(int i){}
void die(int i){exit(0);}

void
dancer()
{
	int	fd;
	for (;;) {
                if ((fd = open("/dev/segled", O_RDWR)) < 0) {
                        perror("open");
                        exit(-1);
                }
		write(fd, "1", 1);
		close(fd);
		usleep(LED_SPEED);
                if ((fd = open("/dev/segled", O_RDWR)) < 0) {
                        perror("open");
                        exit(-1);
                }
		write(fd, "2", 1);
                close(fd);
		usleep(LED_SPEED);
                if ((fd = open("/dev/segled", O_RDWR)) < 0) {
                        perror("open");
                        exit(-1);
		}
		write(fd, "4", 1);
                close(fd);
		usleep(LED_SPEED);
                if ((fd = open("/dev/segled", O_RDWR)) < 0) {
                        perror("open");
                        exit(-1);
                }
                write(fd, "2", 1);
                close(fd);
		usleep(LED_SPEED);
	}
}

int
main(int argc, char *argv[])
{
	int fd, rv, arg;
	int pid;

	if (getuid()) {
		fprintf(stderr, "must be super user\n");
		return 1;
	}

	if ((pid = fork())) {
		/* parent */
		char tmp[100];
		if ((fd = open(PID_FILE, O_CREAT|O_WRONLY|O_TRUNC)) < 0) {
			perror("open");
			exit(-1);
		}
		sprintf(tmp, "%d\n", pid);
		if (write(fd, tmp, strlen(tmp)) != strlen(tmp)) {
			perror("write");
			close(fd);
			exit(-2);
		}
		close(fd);
		return 0;
	} else {
		/* child */
		signal( SIGHUP,donothing);
		signal( SIGINT,die);
		signal( SIGQUIT,die);
		signal( SIGILL,die);
		signal( SIGTRAP,die);
		signal( SIGABRT,die);
		signal( SIGIOT,die);
		signal( SIGBUS,die);
		signal( SIGFPE,die);
		signal( SIGKILL,die);
		signal( SIGUSR1,die);
		signal( SIGSEGV,die);
		signal( SIGUSR2,die);
		signal( SIGPIPE,die);
		signal( SIGALRM,die);
		signal( SIGTERM,die);
		signal( SIGSTKFLT,die);
		signal( SIGCHLD,die);
		signal( SIGCONT,die);
		signal( SIGSTOP,die);
		signal( SIGTSTP,die);
		signal( SIGTTIN,die);
		signal( SIGTTOU,die);
		signal( SIGURG,die);
		signal( SIGXCPU,die);
		signal( SIGXFSZ,die);
		signal( SIGVTALRM,die);
		signal( SIGPROF,die);
		signal( SIGWINCH,die);
		signal( SIGIO,die);
		signal( SIGPWR,die);
		signal( SIGSYS,die);
		dancer();
	}
}
