#	$ssdlinux: Makefile,v 1.11 2004/04/02 02:48:49 yamagata Exp $

.include <bsd.own.mk>

PROG=		e2fsck
SRCS=		dict.c unix.c e2fsck.c super.c \
		pass1.c pass1b.c pass2.c pass3.c pass4.c pass5.c \
		journal.c swapfs.c badblocks.c util.c dirinfo.c dx_dirinfo.c \
		ehandler.c problem.c message.c recovery.c region.c \
		revoke.c ea_refcount.c rehash.c 
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/${PROG}

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

.if ${TARGET_HOSTTYPE} == "i386"
LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
.elif ${TARGET_HOSTTYPE} == "powerpc"
LDADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
LDADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
LDADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
LDADD+=		${LIBE2FSDIR}/libuuid/libuuid.a
.endif
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
DPADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/${PROG}/${.TARGET}.in ${.TARGET}

LINKS+=		${BINDIR}/${PROG} ${BINDIR}/fsck.ext2
.if ${USE_EXT3FS} == "yes"
LINKS+=		${BINDIR}/${PROG} ${BINDIR}/fsck.ext3
.endif

.include <bsd.prog.mk>
