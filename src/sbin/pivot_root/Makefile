#	$ssdlinux: Makefile,v 1.5 2004/06/07 03:30:01 yamagata Exp $

.include <bsd.own.mk>

PROG=		pivot_root
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/mount

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
