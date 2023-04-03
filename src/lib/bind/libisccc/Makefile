#	$ssdlinux: Makefile,v 1.3 2003/10/24 03:04:38 kanoh Exp $

.include <bsd.own.mk>

LIB=		isccc
MKMAN=		no

CPPFLAGS+=	-DLIBINTERFACE=1
CPPFLAGS+=	-DLIBREVISION=0
CPPFLAGS+=	-DLIBAGE=1

DIST=		${.CURDIR}/../../../dist/bind/lib/isccc
.PATH:		${DIST}

CPPFLAGS+=	-I${ISCDIST}
CPPFLAGS+=	-I${ISCDIST}/include
CPPFLAGS+=	-I${ISCDIST}/unix/include
CPPFLAGS+=	-I${ISCDIST}/nothreads/include

.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif

# ${DIST}
CPPFLAGS+=	-I${DIST}/include
SRCS=		alist.c base64.c cc.c ccmsg.c lib.c result.c sexpr.c symtab.c version.c

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
