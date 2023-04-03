#	$ssdlinux: Makefile,v 1.4 2002/11/12 02:09:38 yamagata Exp $

.include <bsd.own.mk>

LIB=		util-linux
SRCS=		err.c my_reboot.c setproctitle.c env.c carefulputc.c xstrncpy.c
SRCS+=		md5.c
MKMAN=		no

DIST=		${.CURDIR}/../../dist/${LIB}
.PATH:		${DIST}/lib

.include "${.CURDIR}/Makefile.cflags"

CPPFLAGS+=	-I${DIST}/lib -I${.CURDIR}/dummy

libinstall::

.include <bsd.lib.mk>
