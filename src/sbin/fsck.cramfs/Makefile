#	$ssdlinux: Makefile,v 1.5 2004/07/04 03:55:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		fsck.cramfs
MKMAN=		no

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/disk-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../zlib
.endif
LDADD=		-L${.CURDIR}/../../lib/libz -lz

.include <bsd.prog.mk>
