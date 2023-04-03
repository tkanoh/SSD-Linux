#	$ssdlinux: Makefile,v 1.1 2003/10/29 08:17:50 yamagata Exp $

.include <bsd.own.mk>

PROG=		tailf

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/text-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
