#	$ssdlinux: Makefile,v 1.1 2004/12/06 05:32:45 yamagata Exp $

.include <bsd.own.mk>

PROG=		flock

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/sys-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
