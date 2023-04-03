#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		lmtp
SRCS=		lmtp.c lmtp_connect.c lmtp_proto.c lmtp_chat.c lmtp_session.c \
		lmtp_addr.c lmtp_trouble.c lmtp_state.c lmtp_sasl_glue.c \
		lmtp_sasl_proto.c 
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
