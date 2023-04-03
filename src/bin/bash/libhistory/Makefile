#	$ssdlinux: Makefile,v 1.3 2004/08/23 02:57:09 yamagata Exp $

.include <bsd.own.mk>

LIB=		history
SRCS=		${LIB}.c histexpand.c \
		histsearch.c histfile.c \
		shell.c
SRCS+=		savestring.c mbutil.c xmalloc.c

DIST=		${.CURDIR}/../../../dist/bash
.PATH:		${DIST}/lib/readline

libinstall::

NOGCCERROR=	yes

.include <bsd.lib.mk>
