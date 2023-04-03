#	$ssdlinux: Makefile,v 1.1 2002/07/01 07:22:47 yamagata Exp $

LIB=		common
SRCS=		getopt.c getopt1.c vfprintf.c number.c

MKPIC=		no
MKLINKLIB=	no

.include "${.CURDIR}/../Makefile.cflags"

.PATH:		${DIST}/lib

NOGCCERROR=	yes

.include <bsd.lib.mk>

