#	$ssdlinux: Makefile,v 1.2 2002/06/05 01:38:48 yamagata Exp $

.include <bsd.own.mk>

PROG=		finger
SRCS=		${PROG}.c lprint.c net.c sprint.c util.c display.c

DIST=		${.CURDIR}/../../dist/usagi-tool/src/bsd-finger/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR}

.include <bsd.prog.mk>
