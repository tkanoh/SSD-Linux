#	$ssdlinux: Makefile,v 1.3 2002/11/27 03:47:35 yamagata Exp $

.include <bsd.own.mk>

PROG=		column

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/text-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
LDADD+=		${LIBULDIR}/err.o

.include <bsd.prog.mk>
