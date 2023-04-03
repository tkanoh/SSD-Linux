#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		smtpd
SRCS=		smtpd.c smtpd_token.c smtpd_check.c smtpd_chat.c smtpd_state.c \
		smtpd_peer.c smtpd_sasl_proto.c smtpd_sasl_glue.c smtpd_proxy.c \
		smtpd_xforward.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

CPPFLAGS+=	-I${DIST}/src/${PROG}

.include <bsd.prog.mk>
