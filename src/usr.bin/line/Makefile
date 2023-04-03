#	$ssdlinux: Makefile,v 1.2 2002/11/27 03:48:56 yamagata Exp $

.include <bsd.own.mk>

PROG=		line

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/text-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
