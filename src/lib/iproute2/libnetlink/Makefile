#	$ssdlinux: Makefile,v 1.2 2002/06/06 01:30:20 yamagata Exp $

.include <bsd.own.mk>

LIB=		netlink
SRCS=		ll_map.c libnetlink.c
MKMAN=		no
DIST=		${.CURDIR}/../../../dist/usagi-tool/src/iproute2/lib
.PATH:		${DIST}

.include "../Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
