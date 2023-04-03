#	$ssdlinux: Makefile,v 1.2 2002/05/31 09:17:59 yamagata Exp $

.include <bsd.own.mk>

PROG=		routed
SRCS=		af.c if.c inet.c input.c main.c output.c startup.c \
		tables.c timer.c trace.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-routed/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

.include <bsd.prog.mk>
