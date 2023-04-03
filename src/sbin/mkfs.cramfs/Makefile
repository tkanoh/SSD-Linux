#	$ssdlinux: Makefile,v 1.6 2004/07/04 03:57:38 yamagata Exp $

.include <bsd.own.mk>

PROG=		mkfs.cramfs
MKMAN=		no

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/disk-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../zlib
.endif
LDADD=		${LIBULDIR}/md5.o
LDADD+=		-L${.CURDIR}/../../lib/libz -lz

.include <bsd.prog.mk>
