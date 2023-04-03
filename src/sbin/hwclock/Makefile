#	$ssdlinux: Makefile,v 1.5 2002/11/27 03:39:14 yamagata Exp $

.include <bsd.own.mk>

PROG=		hwclock
SRCS=		${PROG}.c cmos.c rtc.c kd.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/${PROG}

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

NOGCCERROR=	yes

.include <bsd.prog.mk>
