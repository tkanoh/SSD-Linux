#	$ssdlinux: Makefile,v 1.3 2004/06/16 23:04:49 kanoh Exp $

.include <bsd.own.mk>

PROG=		blkid
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

LDADD+=		-L${LIBE2FSDIR}/libblkid -lblkid
LDADD+=		-L${LIBE2FSDIR}/libuuid -luuid
DPADD+=		${LIBE2FSDIR}/libblkid/libblkid.a
DPADD+=		${LIBE2FSDIR}/libuuid/libuuid.a

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/${.TARGET}.in ${.TARGET}

.include <bsd.prog.mk>
