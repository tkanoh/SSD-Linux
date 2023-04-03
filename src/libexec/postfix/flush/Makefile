#	$ssdlinux: Makefile,v 1.2 2002/12/26 01:20:19 yamagata Exp $

.include <bsd.own.mk>

PROG=		flush
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
