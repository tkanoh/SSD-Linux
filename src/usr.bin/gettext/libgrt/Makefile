#	$ssdlinux: Makefile,v 1.3 2005/02/25 07:03:12 yamagata Exp $

.include <bsd.own.mk>

LIB=		grt
SRCS=		allocsa.c basename.c closeout.c fwriteerror.c progname.c progreloc.c xmalloc.c xstrdup.c xreadlink.c

MKPIC=		no
MKPROFILE=	no
MKLINT=		no

.include "${.CURDIR}/../Makefile.inc.grt"
.PATH:		${DIST}/gettext/gettext-tools/lib
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=      -I${DIST}/gettext/gettext-tools/lib

libinstall::

.include <bsd.lib.mk>
