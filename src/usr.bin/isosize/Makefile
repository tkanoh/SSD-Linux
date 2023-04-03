#	$ssdlinux: Makefile,v 1.3 2002/11/27 03:23:35 yamagata Exp $

.include <bsd.own.mk>

PROG=		isosize
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/disk-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
