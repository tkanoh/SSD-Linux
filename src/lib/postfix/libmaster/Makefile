#	$ssdlinux: Makefile,v 1.3 2004/05/24 05:38:58 yamagata Exp $

.include <bsd.own.mk>

LIB=		master
SRCS=		single_server.c multi_server.c trigger_server.c master_proto.c \
		mail_flow.c

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${LIB}

libinstall::

.include <bsd.lib.mk>
