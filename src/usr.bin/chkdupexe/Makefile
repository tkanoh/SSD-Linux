#	$ssdlinux: Makefile,v 1.3 2002/11/28 06:48:20 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	chkdupexe
MAN=		${SCRIPTS}.1
CLEANFILES=	${SCRIPTS}

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/misc-utils

${SCRIPTS}:
	cp ${DIST}/misc-utils/${.TARGET}.pl ${.TARGET}

.include <bsd.prog.mk>
