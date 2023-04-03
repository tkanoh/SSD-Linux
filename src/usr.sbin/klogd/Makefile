#	$ssdlinux: Makefile,v 1.3 2002/06/06 04:09:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		klogd
SRCS=		${PROG}.c syslog.c pidfile.c ksym.c ksym_mod.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/sysklogd	
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+= 	-DSYSV -fomit-frame-pointer -Wall -fno-strength-reduce \
		-DSYSLOGD_PIDNAME=\"klogd.pid\" -DFSSTND -DALLOW_KERNEL_LOGGING

.include <bsd.prog.mk>
