#	$ssdlinux: Makefile,v 1.11 2004/12/24 07:12:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		mount
SRCS=		${PROG}.c fstab.c sundries.c xmalloc.c realpath.c mntent.c version.c \
		get_label_uuid.c mount_by_label.c mount_blkid.c mount_guess_fstype.c \
		getusername.c \
		lomount.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/util-linux
.PATH:		${DIST}/${PROG}

LIBULDIR=	${.CURDIR}/../../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-DHAVE_BLKID
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
LDADD+=		${LIBULDIR}/setproctitle.o
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

proginstall:

.include <bsd.prog.mk>
