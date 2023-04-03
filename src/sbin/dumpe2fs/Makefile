#	$ssdlinux: Makefile,v 1.3 2002/06/06 00:51:07 yamagata Exp $

.include <bsd.own.mk>

PROG=		dumpe2fs
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libe2p -le2p
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libe2p/libe2p.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/${.TARGET}.in ${.TARGET}

.include <bsd.prog.mk>
