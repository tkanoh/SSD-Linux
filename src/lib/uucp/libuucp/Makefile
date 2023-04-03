#	$ssdlinux: Makefile,v 1.2 2003/06/12 08:51:14 yamagata Exp $

.include <bsd.own.mk>

LIB=		uucp
SRCS=		buffer.c crc.c debug.c escape.c getopt.c getop1.c \
		parse.c quote.c quotes.c spool.c status.c xfree.c xmall.c xreall.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/uucp
.PATH:		${DIST}/lib

CPPFLAGS+=	-I${DIST}/lib -I${DIST}

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
