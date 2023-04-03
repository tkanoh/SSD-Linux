#	$ssdlinux: Makefile,v 1.13 2004/12/24 02:25:16 yamagata Exp $

.include <bsd.own.mk>

PROG=		mount
SRCS=		${PROG}.c fstab.c sundries.c xmalloc.c realpath.c mntent.c version.c \
		get_label_uuid.c mount_by_label.c mount_blkid.c mount_guess_fstype.c \
		getusername.c \
		nfsmount.c nfsmount_xdr.c nfsmount_clnt.c lomount.c
MAN=		${PROG}.8 fstab.5 nfs.5
BINMODE=	4555
CLEANFILES=	nfsmount.x nfsmount.h nfsmount_xdr.c nfsmount_clnt.c

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/${PROG}

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-DHAVE_NFS
CPPFLAGS+=	-DHAVE_BLKID
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DESTDIR}/usr/include
.endif
LDADD+=		${LIBULDIR}/setproctitle.o
LDADD+=		${LIBULDIR}/env.o
LDADD+=		${LIBULDIR}/xstrncpy.o

LIBE2FSDIR=     ${DIST}/../../lib/e2fsprogs
.if ${TARGET_HOSTTYPE} == "i386"
LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
.elif ${TARGET_HOSTTYPE} == "powerpc"
LDADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
LDADD+=		${LIBE2FSDIR}/libuuid/libuuid.a
.endif
DPADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a

NOGCCERROR=	yes

sundries.c: nfsmount.h

nfsmount.h:
	cp ${DIST}/${PROG}/nfsmount.x ${.CURDIR}
	rm -f ${.TARGET}
	rpcgen -h -o ${.TARGET} nfsmount.x

nfsmount_xdr.c: nfsmount.h
	rm -f ${.TARGET}
	rpcgen -c -o ${.TARGET} nfsmount.x

nfsmount_clnt.c: nfsmount.h
	rm -f ${.TARGET}
	rpcgen -l -o ${.TARGET} nfsmount.x

.include <bsd.prog.mk>
