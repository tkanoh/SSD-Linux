#	$ssdlinux: Makefile,v 1.4 2002/11/27 03:46:18 yamagata Exp $

.include <bsd.own.mk>

PROG=		col

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/text-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
