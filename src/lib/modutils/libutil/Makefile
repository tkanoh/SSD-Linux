#	$ssdlinux: Makefile,v 1.5 2004/07/13 05:16:51 yamagata Exp $

.include <bsd.own.mk>

LIB=		util
SRCS=		xmalloc.c xrealloc.c xstrcat.c xstrdup.c xsystem.c \
		logger.c modstat.c \
		meta_expand.c config.c snap_shot.c arch64.c gzfiles.c sys_nim.c \
		xftw.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/modutils
.PATH:		${DIST}/${LIB}

.include "${.CURDIR}/../Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
