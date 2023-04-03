#	$ssdlinux: Makefile,v 1.2 2002/05/31 09:40:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		uuidgen
MAN=		${PROG}.1

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/${.TARGET}.in ${.TARGET}

.include <bsd.prog.mk>
