#	$ssdlinux: Makefile,v 1.3 2003/07/10 07:02:15 yamagata Exp $

.include <bsd.own.mk>

PROG=		chattr
MAN=		${PROG}.1

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libe2p -le2p
LDADD+=		-L${LIBE2FSDIR}/libcom_err -lcom_err
DPADD+=		${LIBE2FSDIR}/libe2p/libe2p.a
DPADD+=		${LIBE2FSDIR}/libcom_err/libcom_err.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/${.TARGET}.in ${.TARGET}

.include <bsd.prog.mk>
