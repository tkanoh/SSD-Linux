#	$ssdlinux: Makefile,v 1.3 2002/05/30 00:57:19 yamagata Exp $

.include <bsd.own.mk>

LIB=		termcap
INCS=		termcap.h
INCSDIR=	/usr/include
MKMAN=		no
MKPIC=		yes
MKPICINSTALL=	no

DIST=		${.CURDIR}/../../dist/termcap
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST} -ansi

SRCS=		termcap.c tparam.c version.c

.include <bsd.lib.mk>
