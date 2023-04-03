#	$ssdlinux: Makefile,v 1.5 2004/11/08 03:30:54 yamagata Exp $

.include <bsd.own.mk>

LIB=		iw
SRCS=		iwlib.c
INCS=		iwlib.h wireless.h
INCSDIR=	/usr/include
MKMAN=		no
MKPIC=		yes
MKPICINSTALL=	no
WE_VERSION=	`sed -ne "/WE_VERSION/{s:\([^0-9]*\)::;p;q;}" ${DIST}/iwlib.h`
CLEANFILES=	wireless.h

DIST=		${.CURDIR}/../../dist/wireless_tools
.PATH:		${DIST}

.include "${.CURDIR}/Makefile.cflags"
.include "${.CURDIR}/Makefile.ldflags"

iwlib.o: wireless.h

wireless.h:
	cp ${DIST}/wireless.${WE_VERSION}.h ${.TARGET}

.include <bsd.lib.mk>
