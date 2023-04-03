#	$ssdlinux: Makefile,v 1.4 2004/11/15 06:02:47 yamagata Exp $

.include <bsd.own.mk>

LIB=		radiusclient		
SRCS=		avpair.c buildreq.c config.c dict.c ip_util.c \
		clientid.c sendserver.c lock.c util.c md5.c

DIST=		${.CURDIR}/../../../../../dist/ppp/pppd/plugins/radius
.PATH:          ${DIST}

CPPFLAGS+=	-I${DIST} -I${DIST}/../.. -I${DIST}/../../../include
CPPFLAGS+=	-fPIC
CPPFLAGS+=	-DRC_LOG_FACILITY=LOG_DAEMON
CPPFLAGS+=	-DCHAPMS=1 -DMPPE=1 -DMAXOCTETS=1

libinstall::

.include <bsd.lib.mk>
