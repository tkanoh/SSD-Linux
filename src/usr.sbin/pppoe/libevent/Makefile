#	$ssdlinux: Makefile,v 1.2 2004/03/06 16:10:20 yamagata Exp $

.include <bsd.own.mk>
.include "${.CURDIR}/../Makefile.inc"

LIB=		event		
SRCS=		${LIB}.c event_tcp.c hash.c event_sig.c

.PATH:          ${DIST}/src/libevent

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
