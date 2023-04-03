#	$ssdlinux: Makefile,v 1.2 2003/10/01 06:07:51 yamagata Exp $
.include <bsd.own.mk>

.include "${.CURDIR}/../Makefile.cflags"

LIB=		dhcpctl
SRCS=		${LIB}.c callback.c remote.c
MAN=		${LIB}.3

DIST=		${.CURDIR}/../../../dist/dhcp
.PATH:		${DIST}/${LIB}

CPPFLAGS+=	-I${DIST} -I${DIST}/includes

libinstall::

.include <bsd.lib.mk>
