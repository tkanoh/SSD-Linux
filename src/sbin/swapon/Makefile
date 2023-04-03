#	$ssdlinux: Makefile,v 1.11 2004/12/25 03:42:54 yamagata Exp $

.include <bsd.own.mk>

PROG=		swapon
MAN=		${PROG}.8 swapoff.8
CLEANFILES=	swapargs.h

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/mount

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-DHAVE_NFS
CPPFLAGS+=	-DHAVE_BLKID
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DESTDIR}/usr/include
.endif
LDADD=		${.CURDIR}/../mount/version.o
LDADD+=		${.CURDIR}/../mount/xmalloc.o
LDADD+=		${.CURDIR}/../mount/get_label_uuid.o
LDADD+=		${.CURDIR}/../mount/mount_by_label.o
LDADD+=		${.CURDIR}/../mount/mount_blkid.o

LIBE2FSDIR=	${DIST}/../../lib/e2fsprogs
.if ${TARGET_HOSTTYPE} == "i386"
LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
.elif ${TARGET_HOSTTYPE} == "powerpc"
LDADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
LDADD+=		${LIBE2FSDIR}/libuuid/libuuid.a
.endif
DPADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a

SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/swapoff

${PROG}.c: swapargs.h

swapargs.h:
	sh ${DIST}/mount/swap.configure

.include <bsd.prog.mk>
