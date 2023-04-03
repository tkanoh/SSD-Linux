#	$ssdlinux: Makefile,v 1.4 2005/03/10 08:43:08 yamagata Exp $

.include <bsd.own.mk>

PROG=		smtp
SRCS=		smtp.c smtp_connect.c smtp_proto.c smtp_chat.c smtp_session.c \
		smtp_addr.c smtp_trouble.c smtp_state.c smtp_rcpt.c \
		smtp_sasl_proto.c smtp_sasl_glue.c smtp_reuse.c smtp_map11.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

CPPFLAGS+=	-I${DIST}/src/${PROG}

.include <bsd.prog.mk>
