#	$ssdlinux: Makefile,v 1.3 2002/11/27 03:41:36 yamagata Exp $

.include <bsd.own.mk>

PROG=		arch

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/sys-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
