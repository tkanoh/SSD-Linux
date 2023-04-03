#	$ssdlinux: Makefile,v 1.3 2002/11/27 03:28:04 yamagata Exp $

.include <bsd.own.mk>

PROG=		ddate

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/misc-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
