#	$ssdlinux: Makefile,v 1.1 2004/03/09 07:55:28 yamagata Exp $

.include <bsd.own.mk>

PROG=		filefrag
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/e2fsprogs
.PATH:		${DIST}/misc

.include "${.CURDIR}/../../lib/e2fsprogs/Makefile.cflags"

CLEANFILES=	${MAN}

${MAN}:
	${UTILDIR}/subst -f ${UTILDIR}/subst.conf ${DIST}/misc/${.TARGET}.in ${.TARGET}

.include <bsd.prog.mk>
