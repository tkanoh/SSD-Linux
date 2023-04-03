#	$ssdlinux: Makefile,v 1.1 2003/01/08 08:18:39 kanoh Exp $

CROSS_BUILD=	powerpc
CROSS_LIB=	yes

.include <bsd.own.mk>

LIB=		termcap
INCS=		termcap.h
MKMAN=		no
MKPIC=		yes
MKPICINSTALL=	no

DIST=		${.CURDIR}/../../../dist/termcap
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST} -ansi

SRCS=		termcap.c tparam.c version.c

.include <bsd.lib.mk>
