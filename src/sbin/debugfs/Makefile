#	$ssdlinux: Makefile,v 1.7 2005/03/02 06:02:01 yamagata Exp $

.include <bsd.own.mk>

PROG=		debugfs
SRCS=		debug_cmds.c debugfs.c util.c ncheck.c icheck.c ls.c \
		lsdel.c dump.c set_fields.c logdump.c htree.c unused.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/${PROG}

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libe2p -le2p
LDADD+=		-L${LIBE2FSDIR}/libss -lss
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
LDADD+=		-ldl
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libe2p/libe2p.a
DPADD+=		${LIBE2FSDIR}/libss/libss.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
DPADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a

CLEANFILES=	${MAN} debug_cmds.c

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/${PROG}/${.TARGET}.in ${.TARGET}

debug_cmds.c:
	_SS_DIR_OVERRIDE=${LIBE2FSDIR}/libss ${LIBE2FSDIR}/libss/mk_cmds ${DIST}/${PROG}/debug_cmds.ct

.include <bsd.prog.mk>
