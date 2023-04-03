#	$ssdlinux: Makefile,v 1.3 2004/06/16 17:18:03 kanoh Exp $

.include <bsd.own.mk>

LIB=		bz2
MKMAN=		no
MKPIC=		yes
MKPICINSTALL=	no

DIST=		${.CURDIR}/../../dist/bzip2
.PATH:		${DIST}

SRCS=		blocksort.c huffman.c crctable.c randtable.c compress.c \
		decompress.c  bzlib.c
INCS=		bzlib.h
INCSDIR=	/usr/include

CPPFLAGS+=	-Wall -Winline -fomit-frame-pointer -fno-strength-reduce
CPPFLAGS+=	-D_FILE_OFFSET_BITS=64	

NOGCCERROR=	yes

.include <bsd.lib.mk>
