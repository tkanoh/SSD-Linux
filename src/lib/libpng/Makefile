#	$ssdlinux: Makefile,v 1.5 2004/08/07 09:13:29 kanoh Exp $

.include <bsd.own.mk>

LIB=		png
SRCS=		png.c pngset.c pngget.c pngrutil.c pngtrans.c \
		pngwutil.c pngread.c pngrio.c pngwio.c pngwrite.c \
		pngrtran.c pngwtran.c pngmem.c pngerror.c pngpread.c
INCS=		png.h pngconf.h
INCSDIR=	/usr/include
MAN=		libpng.3 libpngpf.3 png.5		
FILES=		libpng-config
FILESMODE=	555
FILESDIR=	/usr/bin

MKPIC=		yes
MKPICLIB=	yes
MKPICINSTALL=	yes

CPPFLAGS+=	-I${DIST} -Wall -O3 -funroll-loops
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../dist/zlib
.endif

DIST=		${.CURDIR}/../../dist/libpng
.PATH:		${DIST}

.include <bsd.lib.mk>
