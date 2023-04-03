#	$ssdlinux: Makefile,v 1.2 2002/10/08 02:55:21 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	uuto
CLEANFILES=	${SCRIPTS}

DIST=		${.CURDIR}/../../../dist/uucp

${SCRIPTS}:
	sed -e 's,@BINDIR@,${BINDIR},' < ${DIST}/${.TARGET}.in > ${.TARGET};

.include <bsd.prog.mk>
