#	$ssdlinux: Makefile,v 1.4 2002/11/27 03:25:04 yamagata Exp $

.include <bsd.own.mk>

PROG=		agetty
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/login-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

LDADD+=		${LIBULDIR}/xstrncpy.o

.include <bsd.prog.mk>
