#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		bounce
SRCS=		bounce.c bounce_append_service.c bounce_notify_service.c \
		bounce_cleanup.c bounce_notify_util.c bounce_notify_verp.c \
		bounce_one_service.c bounce_warn_service.c bounce_trace_service.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
