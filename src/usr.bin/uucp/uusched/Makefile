#	$ssdlinux: Makefile,v 1.2 2002/10/08 02:52:40 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	uusched
CLEANFILES=	${SCRIPTS}

DIST=		${.CURDIR}/../../../dist/uucp

${SCRIPTS}:
	sed -e 's,@SBINDIR@,/usr/libexec/uucp,' < ${DIST}/${.TARGET}.in > ${.TARGET};

.include <bsd.prog.mk>
