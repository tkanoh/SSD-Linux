#	$ssdlinux: Makefile,v 1.2 2003/10/01 06:09:29 yamagata Exp $
.include <bsd.own.mk>

.include "${.CURDIR}/../Makefile.cflags"

LIB=		dst
SRCS=		dst_support.c dst_api.c hmac_link.c md5_dgst.c base64.c prandom.c
MKMAN=	no

DIST=		${.CURDIR}/../../../dist/dhcp
.PATH:		${DIST}/${LIB}

CPPFLAGS+=	-I${DIST} -I${DIST}/includes
CPPFLAGS+=	-DHMAC_MD5 -DMINIRES_LIB

libinstall::

.include <bsd.lib.mk>
