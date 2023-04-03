#	$ssdlinux: Makefile,v 1.9 2003/11/11 02:04:02 yamagata Exp $

.include <bsd.own.mk>

PROG=		mke2fs
SRCS=		${PROG}.c util.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
LDADD+=		-L${LIBE2FSDIR}/libe2p -le2p
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
DPADD+=		${LIBE2FSDIR}/libbldid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a
DPADD+=		${LIBE2FSDIR}/libe2p/libe2p.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/${.TARGET}.in ${.TARGET}

LINKS+=		${BINDIR}/${PROG} ${BINDIR}/mkfs.ext2
.if ${USE_EXT3FS} == "yes"
LINKS+=		${BINDIR}/${PROG} ${BINDIR}/mkfs.ext3
.endif

.include <bsd.prog.mk>
