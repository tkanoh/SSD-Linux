#	$ssdlinux: Makefile,v 1.10 2004/12/24 07:12:02 yamagata Exp $

.include <bsd.own.mk>

PROG=		umount
SRCS=		${PROG}.c fstab.c sundries.c xmalloc.c realpath.c mntent.c getusername.c \
		get_label_uuid.c mount_by_label.c mount_blkid.c version.c lomount.c
MKMAN=		no
CLEANFILES=	nfsmount.x nfsmount.h

DIST=		${.CURDIR}/../../../dist/util-linux
.PATH:		${DIST}/mount

LIBULDIR=	${.CURDIR}/../../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-DHAVE_NFS
CPPFLAGS+=	-DHAVE_BLKID
CPPFLAGS+=	-Derror=mount_error
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
LDADD+=		${LIBULDIR}/env.o
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

${PROG}.c: nfsmount.h

nfsmount.h:
	rm -f ${.TARGET}
	cp ${DIST}/mount/nfsmount.x ${.CURDIR}
	rpcgen -h -o ${.TARGET} nfsmount.x

proginstall:

.include <bsd.prog.mk>
