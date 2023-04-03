#	$ssdlinux: Makefile,v 1.4 2004/08/06 05:48:42 yamagata Exp $

.include <bsd.own.mk>

LIB=	readline
SRCS=	readline.c vi_mode.c funmap.c keymaps.c parens.c search.c \
	rltty.c complete.c bind.c isearch.c display.c signals.c \
	util.c kill.c undo.c macro.c input.c callback.c terminal.c \
	text.c nls.c misc.c compat.c xmalloc.c history.c histexpand.c \
	histfile.c histsearch.c shell.c mbutil.c tilde.c
INCS=	readline.h chardefs.h keymaps.h history.h tilde.h rlstdc.h \
	rlconf.h rltypedefs.h
MAN=	${LIB}.3

.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/..
.endif
.if defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${DIST}/../ncurses/include
.endif
NOGCCERROR=	yes

.include <bsd.lib.mk>
