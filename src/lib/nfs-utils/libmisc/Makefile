#	$ssdlinux: Makefile,v 1.2 2003/09/04 08:23:45 yamagata Exp $

.include <bsd.own.mk>

LIB=		misc
SRCS=		tcpwrapper.c from_local.c mountpoint.c
MKPIC=		no
MKMAN=		no
DIST=		${.CURDIR}/../../../dist/nfs-utils
.PATH:		${DIST}/support/misc

.include "${.CURDIR}/../Makefile.cflags"

NOGCCERROR=	yes

.include <bsd.lib.mk>
