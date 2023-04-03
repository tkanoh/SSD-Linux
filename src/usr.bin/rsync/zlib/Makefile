#	$ssdlinux: Makefile,v 1.1 2002/05/21 03:52:45 kanoh Exp $

.include 	<bsd.own.mk>

LIB=		zlib
SRCS=		deflate.c infblock.c infcodes.c inffast.c inflate.c \
		inftrees.c infutil.c trees.c zutil.c adler32.c

DIST=		${.CURDIR}/../../../dist/rsync
.PATH:		${DIST}/zlib

CPPFLAGS+=	-I${.CURDIR}/../ -I${DIST}

libinstall::

.include <bsd.lib.mk>
