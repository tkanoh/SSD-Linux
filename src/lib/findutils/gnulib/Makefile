#	$ssdlinux: Makefile,v 1.2 2005/01/31 02:23:05 yamagata Exp $

.include <bsd.own.mk>

LIB=		gnulib
SRCS=		mktime.c mountlist.c
SRCS+=		argmatch.c canonicalize.c \
		closeout.c cycle-check.c dirname.c \
		basename.c stripslash.c exitfail.c \
		filemode.c human.c idcache.c \
		modechange.c path-concat.c quote.c \
		quotearg.c savedir.c strftime.c \
		xmalloc.c xalloc-die.c xgetcwd.c \
		xreadlink.c xstrtol.c xstrtoul.c \
		xstrtoumax.c yesno.c
MKMAN=		no
DIST=		${.CURDIR}/../../../dist/findutils
.PATH:		${DIST}/gnulib/lib

CPPFLAGS+=	-DHAVE_CONFIG_H -I${DIST}/gnulib/lib -I${.CURDIR}/..

libinstall::

.include <bsd.lib.mk>
