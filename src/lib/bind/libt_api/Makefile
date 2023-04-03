#	$ssdlinux: Makefile,v 1.3 2005/03/14 03:46:46 yamagata Exp $

.include <bsd.own.mk>

LIB=		t_api
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/bind/lib/tests
.PATH:		${DIST}

CPPFLAGS+=	-I${ISCDIST}
CPPFLAGS+=	-I${ISCDIST}/include
CPPFLAGS+=	-I${ISCDIST}/unix/include
CPPFLAGS+=	-I${ISCDIST}/nothreads/include

.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif

DNSDIST=	${.CURDIR}/../../../dist/bind/lib/dns
CPPFLAGS+=	-I${DNSDIST}/include
CPPFLAGS+=	-I${DIST}/include
SRCS=		t_api.c

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
