#	$ssdlinux: Makefile,v 1.4 2002/11/27 03:29:14 yamagata Exp $

.include <bsd.own.mk>

PROG=		mcookie

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/misc-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

LDADD=		${LIBULDIR}/md5.o

.include <bsd.prog.mk>
