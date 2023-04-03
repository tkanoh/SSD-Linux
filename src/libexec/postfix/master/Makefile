#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		master
SRCS=		master.c master_conf.c master_ent.c master_sig.c master_avail.c \
		master_spawn.c master_service.c master_status.c master_listen.c \
		master_vars.c master_wakeup.c master_flow.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
