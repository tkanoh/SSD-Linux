#	$ssdlinux: Makefile,v 1.8 2003/07/16 06:51:57 yamagata Exp $
#	$NetBSD: Makefile,v 1.48 1999/02/05 22:19:47 tron Exp $
#	@(#)Makefile	8.4 (Berkeley) 5/5/95

.include <bsd.own.mk>

YHEADER=	1
PROG=		sh
SHSRCS=		alias.c cd.c echo.c error.c eval.c exec.c expand.c \
		histedit.c input.c jobs.c mail.c main.c memalloc.c miscbltin.c \
		mystring.c options.c parser.c redir.c show.c test.c times.c \
		trap.c output.c var.c setmode.c
GENSRCS=	arith.c arith.h arith_lex.c builtins.c builtins.h init.c \
		nodes.c signames.c nodes.h syntax.c syntax.h token.h
SRCS=		${SHSRCS} ${GENSRCS}

LDADD+=		-L${.CURDIR}/../../lib/libfl -lfl
DPADD+=		${.CURDIR}/../../lib/libfl.a

LFLAGS=		-8	# 8-bit lex scanner for arithmetic
YACC=		yacc

CPPFLAGS+=	-DSMALL -DSHELL -I${.CURDIR} -D__BIT_TYPES_DEFINED__

.PATH:		${.CURDIR}/bltin

CLEANFILES+=	mkinit mknodes mksyntax mksignames
CLEANFILES+=	${GENSRCS} y.tab.h

token.h: mktokens
	sh ${.ALLSRC}

builtins.c builtins.h: mkbuiltins shell.h builtins.def
	sh ${.ALLSRC} ${.OBJDIR}

init.c: mkinit ${SHSRCS}
	./${.ALLSRC}

nodes.c nodes.h: mknodes nodetypes nodes.c.pat
	./${.ALLSRC}

syntax.c syntax.h: mksyntax
	./${.ALLSRC}

signames.c: mksignames
	./${.ALLSRC}

mkinit: mkinit.c
	${HOST_LINK.c} -o mkinit ${.IMPSRC}

mknodes: mknodes.c
	${HOST_LINK.c} -o mknodes ${.IMPSRC}

.if ${TARGET_HOSTTYPE} == "powerpc"
TARGET_CHARFLAG=	-DTARGET_CHAR="u_int8_t"
.else
TARGET_CHARFLAG=	-DTARGET_CHAR="int8_t"
.endif

mksyntax: mksyntax.c
	${HOST_LINK.c} ${TARGET_CHARFLAG} -o mksyntax ${.IMPSRC}

mksignames: mksignames.c
	${HOST_LINK.c} ${CPPFLAGS} -o mksignames ${.IMPSRC}

NOGCCERROR=	YES

proginstall:

.include <bsd.prog.mk>

${OBJS}: builtins.h nodes.h syntax.h token.h
