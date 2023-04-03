#	$ssdlinux: Makefile,v 1.1 2002/07/04 01:02:49 yamagata Exp $

.include <bsd.own.mk>

PROG=		lesskey
CLEANFILES=	${PROG}.1

DIST=		${.CURDIR}/../../../dist/less
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}/../less

LDADD+=		${.CURDIR}/../less/version.o

${PROG}.1: ${DIST}/${PROG}.nro
	cat ${DIST}/${PROG}.nro > ${.TARGET}

.include <bsd.prog.mk>
