#	$ssdlinux: Makefile,v 1.2 2002/12/26 01:24:36 yamagata Exp $

.include <bsd.own.mk>

PROG=		qmqpd
SRCS=		qmqpd.c qmqpd_state.c qmqpd_peer.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

CPPFLAGS+=	-I${DIST}/src/${PROG}

.include <bsd.prog.mk>
