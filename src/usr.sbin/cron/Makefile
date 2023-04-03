#	$ssdlinux: Makefile,v 1.5 2004/06/15 08:49:12 yamagata Exp $

.include <bsd.own.mk>

PROG=		cron
SRCS=		${PROG}.c database.c user.c job.c do_command.c popen.c
MAN=		${PROG}.8 bitstring.3

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR} -I${DIST}
LDADD+=		${.CURDIR}/../../usr.bin/crontab/compat.o \
		${.CURDIR}/../../usr.bin/crontab/env.o \
		${.CURDIR}/../../usr.bin/crontab/entry.o \
		${.CURDIR}/../../usr.bin/crontab/misc.o

.include <bsd.prog.mk>
