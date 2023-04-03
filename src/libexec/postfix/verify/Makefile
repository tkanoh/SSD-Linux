#	$ssdlinux: Makefile,v 1.1 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		verify
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
