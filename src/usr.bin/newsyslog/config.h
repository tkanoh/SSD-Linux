/*	$ssdlinux: config.h,v 1.3 2003/10/07 01:44:03 yamagata Exp $	*/
/* config.h.  Generated by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */

/* Compressed file suffix string */
#define COMPRESS_SUFFIX ".gz"

/* Define to 1 if you have the `bzero' function. */
#define HAVE_BZERO 1

/* Define to 1 if you have the declaration of `sig2str', and to 0 if you
   don't. */
#define HAVE_DECL_SIG2STR 0

/* Define to 1 if you have the declaration of `str2sig', and to 0 if you
   don't. */
#define HAVE_DECL_STR2SIG 0

/* Define to 1 if you have the declaration of `strchr', and to 0 if you don't.
   */
#define HAVE_DECL_STRCHR 1

/* Define to 1 if you have the declaration of `strdup', and to 0 if you don't.
   */
#define HAVE_DECL_STRDUP 1

/* Define to 1 if you have the declaration of `strptime', and to 0 if you
   don't. */
#define HAVE_DECL_STRPTIME 0

/* Define to 1 if you have the declaration of `strrchr', and to 0 if you
   don't. */
#define HAVE_DECL_STRRCHR 1

/* Define to 1 if you have the declaration of `strsignal', and to 0 if you
   don't. */
#define HAVE_DECL_STRSIGNAL 0

/* Define to 1 if you have the declaration of `strtok', and to 0 if you don't.
   */
#define HAVE_DECL_STRTOK 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the `flock' function. */
#define HAVE_FLOCK 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `isinf' function. */
#define HAVE_ISINF 1

/* Define to 1 if you have the `isnan' function. */
#define HAVE_ISNAN 1

/* Define to 1 if you have the <linux/tasks.h> header file. */
/* #undef HAVE_LINUX_TASKS_H */

/* Define to 1 if you have the <linux/threads.h> header file. */
#define HAVE_LINUX_THREADS_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkstemp' function. */
#define HAVE_MKSTEMP 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the `rename' function. */
#define HAVE_RENAME 1

/* Define to 1 if you have the `sig2str' function. */
/* #undef HAVE_SIG2STR */

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `str2sig' function. */
/* #undef HAVE_STR2SIG */

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strptime' function. */
#define HAVE_STRPTIME 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strsignal' function. */
#define HAVE_STRSIGNAL 1

/* Define to 1 if you have the `strtok' function. */
#define HAVE_STRTOK 1

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the `sys_nsig' function. */
/* #undef HAVE_SYS_NSIG */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/proc.h> header file. */
/* #undef HAVE_SYS_PROC_H */

/* Define to 1 if you have the `sys_signame' function. */
/* #undef HAVE_SYS_SIGNAME */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/user.h> header file. */
#define HAVE_SYS_USER_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if the system has the type `unsigned long long'. */
#define HAVE_UNSIGNED_LONG_LONG 1

/* Name of package */
#define PACKAGE "newsyslog"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "woods-newsyslog@robohack.planix.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "NewSyslog"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "NewSyslog 1.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "newsyslog"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.1"

/* File compression program pathname */
#define PATH_COMPRESS "/usr/bin/gzip"

/* Default path to the configuration file */
#define PATH_CONFIG "/etc/newsyslog.conf"

/* Pathname of syslogd's default PID file */
#define PATH_SYSLOGD_PIDFILE "/var/run/syslogd.pid"

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if <signal.h> declares 'sys_nsig' */
/* #undef SYS_NSIG_DECLARED */

/* Define if <signal.h> declares 'sys_signame' */
/* #undef SYS_SIGNAME_DECLARED */

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Version number of package */
#define VERSION "1.1"

/* Define if using the dmalloc debugging malloc package */
/* #undef WITH_DMALLOC */

/* Define to 1 if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* # undef _ALL_SOURCE */
#endif

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */