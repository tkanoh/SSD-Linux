#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:41:27 yamagata Exp $

.include <bsd.own.mk>

PROG=		virtual
SRCS=		virtual.c mailbox.c recipient.c deliver_attr.c maildir.c unknown.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
