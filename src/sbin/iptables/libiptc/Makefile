#	$ssdlinux: Makefile,v 1.3 2005/02/14 03:03:31 yamagata Exp $

.include <bsd.own.mk>

LIB=		iptc
SRCS=		libip4tc.c libip6tc.c 

DIST=		${.CURDIR}/../../../dist/iptables
.PATH:		${DIST}/libiptc

.include "${.CURDIR}/../../../lib/iptables/Makefile.cflags"

libinstall::

NOGCCERROR=	yes

.include <bsd.lib.mk>
