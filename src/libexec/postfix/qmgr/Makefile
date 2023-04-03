#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:43:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		qmgr
SRCS=		qmgr.c qmgr_active.c qmgr_transport.c qmgr_queue.c qmgr_entry.c \
		qmgr_message.c qmgr_deliver.c qmgr_move.c qmgr_rcpt_list.c \
		qmgr_job.c qmgr_peer.c \
		qmgr_defer.c qmgr_enable.c qmgr_scan.c qmgr_bounce.c
MANPREFIX=	8
MAN=		${PROG}.${MANPREFIX}

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man${MANPREFIX}

.include <bsd.prog.mk>
