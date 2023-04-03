#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		cleanup
SRCS=		cleanup.c cleanup_out.c cleanup_envelope.c cleanup_message.c \
		cleanup_extracted.c cleanup_state.c cleanup_rewrite.c \
		cleanup_map11.c cleanup_map1n.c cleanup_masquerade.c \
		cleanup_out_recipient.c cleanup_init.c cleanup_api.c \
		cleanup_addr.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
