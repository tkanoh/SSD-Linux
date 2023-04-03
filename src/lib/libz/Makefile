#	$ssdlinux: Makefile,v 1.3 2003/12/24 01:22:56 yamagata Exp $

.include <bsd.own.mk>

LIB=		z
MKMAN=		zlib.3
INCS=		zlib.h zconf.h
INCSDIR=	/usr/include
MKPIC=		yes
MKPICINSTALL=	no

DIST=		${.CURDIR}/../../dist/zlib
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST} -fPIC -DHAVE_UNISTD_H -DUSE_MMAP

SRCS=		adler32.c compress.c crc32.c gzio.c uncompr.c \
		deflate.c trees.c zutil.c inflate.c infback.c \
		inftrees.c inffast.c		

.include <bsd.lib.mk>
