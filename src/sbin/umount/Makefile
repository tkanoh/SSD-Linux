#	$ssdlinux: Makefile,v 1.10 2004/12/24 02:25:37 yamagata Exp $

.include <bsd.own.mk>

PROG=		umount
MAN=		${PROG}.8
BINMODE=	4555

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/mount

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-DHAVE_NFS
CPPFLAGS+=	-DHAVE_BLKID
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${.CURDIR}/../mount
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
LDADD=		${.CURDIR}/../mount/fstab.o
LDADD+=		${.CURDIR}/../mount/sundries.o
LDADD+=		${.CURDIR}/../mount/xmalloc.o
LDADD+=		${.CURDIR}/../mount/realpath.o
LDADD+=		${.CURDIR}/../mount/mntent.o
LDADD+=		${.CURDIR}/../mount/getusername.o
LDADD+=		${.CURDIR}/../mount/get_label_uuid.o
LDADD+=		${.CURDIR}/../mount/mount_by_label.o
LDADD+=		${.CURDIR}/../mount/mount_blkid.o
LDADD+=		${.CURDIR}/../mount/version.o
LDADD+=		${LIBULDIR}/env.o
LDADD+=		${.CURDIR}/../mount/lomount.o
LDADD+=		${LIBULDIR}/xstrncpy.o

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

.include <bsd.prog.mk>
