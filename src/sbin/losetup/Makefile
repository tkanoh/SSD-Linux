#	$ssdlinux: Makefile,v 1.9 2004/08/30 03:49:02 yamagata Exp $

.include <bsd.own.mk>

PROG=		losetup
SRCS=		lomount.c
MAN=		${PROG}.8
CLEANFILES=	loop.h

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/mount

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${.CURDIR}/../mount
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
CPPFLAGS+=	-DHAVE_NFS
CPPFLAGS+=	-DHAVE_BLKID
CPPFLAGS+=	-DMAIN
LDADD+=		${LIBULDIR}/xstrncpy.o

.include <bsd.prog.mk>
