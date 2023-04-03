#	$ssdlinux: Makefile,v 1.4 2003/10/24 03:04:38 kanoh Exp $

.include <bsd.own.mk>

LIB=		isccfg
MKMAN=		no

CPPFLAGS+=	-DLIBINTERFACE=0
CPPFLAGS+=	-DLIBREVISION=7
CPPFLAGS+=	-DLIBAGE=0

DIST=		${.CURDIR}/../../../dist/bind/lib/isccfg
.PATH:		${DIST}

CPPFLAGS+=	-I${ISCDIST}
CPPFLAGS+=	-I${ISCDIST}/include
CPPFLAGS+=	-I${ISCDIST}/unix/include
CPPFLAGS+=	-I${ISCDIST}/nothreads/include
CPPFLAGS+=	-I${ISCDIST}/../dns/include

.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif

# ${DIST}
CPPFLAGS+=	-I${DIST}/include
SRCS=		check.c log.c parser.c version.c

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
