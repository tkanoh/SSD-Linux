#	$ssdlinux: Makefile,v 1.3 2004/06/16 22:56:50 kanoh Exp $

.include <bsd.own.mk>

LIB=		util
SRCS=		utils.c rt_names.c ll_types.c ll_proto.c ll_addr.c \
		inet_proto.c  dnet_ntop.c dnet_pton.c ipx_ntop.c ipx_pton.c
MKMAN=		no
DIST=		${.CURDIR}/../../../dist/usagi-tool/src/iproute2/lib
.PATH:		${DIST}

.include "../Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
