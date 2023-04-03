#	$ssdlinux: Makefile,v 1.3 2004/11/24 01:14:42 yamagata Exp $

LIB=		pammodutil
SRCS=		modutil_cleanup.c modutil_getpwnam.c modutil_getpwuid.c
MKMAN=		no

.include "${.CURDIR}/../Makefile.cflags"

.PATH:		${MSRCDIR}/${LIB}

CPPFLAGS+=	-I${MSRCDIR}/pammodutil/include

libinstall::

.include <bsd.lib.mk>
