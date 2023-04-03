#	$ssdlinux: Makefile,v 1.2 2002/06/04 03:56:51 yamagata Exp $

.include <bsd.own.mk>

PROG=		badblocks
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libext2fs -lext2fs
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
DPADD+=		${LIBE2FSDIR}/libext2fs/libext2fs.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/${.TARGET}.in ${.TARGET}

.include <bsd.prog.mk>
