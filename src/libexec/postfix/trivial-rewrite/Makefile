#	$ssdlinux: Makefile,v 1.2 2002/12/26 01:26:52 yamagata Exp $

.include <bsd.own.mk>

PROG=		trivial-rewrite
SRCS=		trivial-rewrite.c rewrite.c resolve.c transport.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

CPPFLAGS+=	-I${DIST}/src/${PROG}

.include <bsd.prog.mk>
