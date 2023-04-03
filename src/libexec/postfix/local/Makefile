#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		local
SRCS=		alias.c command.c delivered.c dotforward.c file.c forward.c \
		include.c indirect.c local.c mailbox.c recipient.c resolve.c token.c \
		deliver_attr.c maildir.c biff_notify.c unknown.c \
		local_expand.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

CPPFLAGS+=	-I${DIST}/src/${PROG}

.include <bsd.prog.mk>
