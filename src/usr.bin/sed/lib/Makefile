#	$ssdlinux: Makefile,v 1.7 2004/01/15 02:18:43 yamagata Exp $

.include <bsd.own.mk>

LIB=		sed
SRCS=		getopt1.c getopt.c utils.c regex.c
MKMAN=		no
CLEANFILES=	regex.h

DIST=		${.CURDIR}/../../../dist/sed
.PATH:		${DIST}/lib

CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-I${.CURDIR}/../include
CPPFLAGS+=	-I${DIST}
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-I${.CURDIR}

regex.c: regex.h

regex.h: ${DIST}/lib/regex_.h
	rm -f ${.TARGET}
	cp ${DIST}/lib/regex_.h ${.TARGET}

libinstall::

NOGCCERROR=	yes

.include <bsd.lib.mk>
