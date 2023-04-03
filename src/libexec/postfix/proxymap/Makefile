#	$ssdlinux: Makefile,v 1.1 2003/01/24 08:09:03 yamagata Exp $

.include <bsd.own.mk>

PROG=		proxymap
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
