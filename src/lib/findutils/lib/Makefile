#	$ssdlinux: Makefile,v 1.2 2005/01/31 02:23:24 yamagata Exp $

.include <bsd.own.mk>

LIB=		find
SRCS=		listfile.c nextelem.c extendbuf.c buildcmd.c savedirinfo.c
MKMAN=		no
DIST=		${.CURDIR}/../../../dist/findutils
.PATH:		${DIST}/lib

CPPFLAGS+=	-DHAVE_CONFIG_H -I${DIST}/lib -I${.CURDIR}/.. -I${DIST}/gnulib/lib

libinstall::

.include <bsd.lib.mk>
