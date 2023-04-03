#	$ssdlinux: Makefile,v 1.6 2004/07/13 02:49:21 yamagata Exp $

.include <bsd.own.mk>

LIB=		com_err
SRCS=		error_message.c et_name.c init_et.c com_err.c com_right.c
MKPIC=		yes
MKPICINSTALL=	no
MKMAN=		no

FILES=		com_err.h
FILESMODE=	444
FILESDIR=	/usr/include/et

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/lib/et

.include "${.CURDIR}/../Makefile.cflags"

.include <bsd.lib.mk>
