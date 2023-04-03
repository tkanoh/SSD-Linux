#	$ssdlinux: Makefile,v 1.4 2004/09/24 06:07:09 yamagata Exp $

.include <bsd.own.mk>

LIB=		lwres
MKMAN=		no

CPPFLAGS+=	-DLIBINTERFACE=2
CPPFLAGS+=	-DLIBREVISION=1
CPPFLAGS+=	-DLIBAGE=1

DIST=		${.CURDIR}/../../../dist/bind/lib/lwres
.PATH:		${DIST}

CPPFLAGS+=	-I${ISCDIST}
CPPFLAGS+=	-I${ISCDIST}/include
CPPFLAGS+=	-I${ISCDIST}/unix/include
CPPFLAGS+=	-I${ISCDIST}/nothreads/include

.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif

CPPFLAGS+=	-I${DIST}/include -I${DIST}/unix/include
SRCS=		context.c gai_strerror.c getaddrinfo.c gethost.c \
		getipnode.c getnameinfo.c getrrset.c herror.c \
		lwbuffer.c lwconfig.c lwpacket.c lwresutil.c \
		lwres_gabn.c lwres_gnba.c lwres_grbn.c lwres_noop.c \
		lwinetaton.c lwinetpton.c lwinetntop.c print.c version.c

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
