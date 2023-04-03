#	$ssdlinux: Makefile,v 1.6 2003/07/10 07:04:45 yamagata Exp $

.include <bsd.own.mk>

PROG=		tune2fs
MAN=		${PROG}.8 e2label.8 findfs.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		${.CURDIR}/../mke2fs/util.o
LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
LDADD+=		-L${LIBE2FSDIR}/libe2p -le2p
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
DPADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a
DPADD+=		${LIBE2FSDIR}/libe2p/libe2p.a

CLEANFILES=	${MAN}

${MAN}:
	for i in ${MAN}; do \
		${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/$$i.in $$i; \
	done

LINKS+=		${BINDIR}/${PROG} ${BINDIR}/e2label
LINKS+=		${BINDIR}/${PROG} ${BINDIR}/findfs

.include <bsd.prog.mk>
