#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:49:01 yamagata Exp $

.include <bsd.own.mk>

LIB=		tc
SRCS=		tc_core.c tc_red.c tc_cbq.c tc_estimator.c		
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/usagi-tool/src/iproute2/tc
.PATH:		${DIST}

LIBIPROUTE2=	${.CURDIR}/../../../lib/iproute2
.include "${LIBIPROUTE2}/Makefile.cflags"
.include "${LIBIPROUTE2}/Makefile.ldflags"

libinstall::

.include <bsd.lib.mk>
