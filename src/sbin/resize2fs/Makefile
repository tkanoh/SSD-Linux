#	$ssdlinux: Makefile,v 1.3 2005/03/02 06:04:04 yamagata Exp $

.include <bsd.own.mk>

PROG=		resize2fs
SRCS=		extent.c resize2fs.c main.c sim_progress.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/resize

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
LDADD+=		-L${LIBE2FSDIR}/libe2p -le2p
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a
DPADD+=		${LIBE2FSDIR}/libe2p/libe2p.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/resize/${.TARGET}.in ${.TARGET}

.include <bsd.prog.mk>
