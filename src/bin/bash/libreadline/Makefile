#	$ssdlinux: Makefile,v 1.3 2004/08/23 03:14:17 yamagata Exp $

.include <bsd.own.mk>

LIB=		readline
SRCS=		${LIB}.c vi_mode.c funmap.c keymaps.c parens.c search.c \
		rltty.c complete.c bind.c isearch.c display.c signals.c \
		util.c kill.c undo.c macro.c input.c callback.c terminal.c \
		text.c nls.c misc.c \
		history.c histexpand.c histfile.c histsearch.c shell.c savestring.c mbutil.c \
		tilde.c \
		xmalloc.c compat.c

DIST=		${.CURDIR}/../../../dist/bash
.PATH:		${DIST}/lib/${LIB}

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
