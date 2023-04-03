#	$ssdlinux: Makefile,v 1.7 2003/01/29 08:47:35 yamagata Exp $

.include <bsd.own.mk>

PROG=		bison
# src
SRCS=		LR0.c assoc.c closure.c complain.c conflicts.c derives.c \
		files.c getargs.c gram.c lalr.c location.c main.c muscle_tab.c \
		nullable.c output.c parse-gram.c print.c print_graph.c \
		reader.c reduce.c relation.c scan-gram.c scan-skel.c state.c \
		symlist.c symtab.c tables.c uniqstr.c vcg.c
# lib
SRCS+=		basename.c dirname.c get-errno.c getopt.c getopt1.c hash.c \
		mbswidth.c quote.c quotearg.c subpipe.c xmalloc.c xstrdup.c \
		xstrndup.c
SRCS+=		abitset.c bitset.c ebitset.c bitsetv.c bitset_stats.c lbitset.c
SRCS+=		bitsetv-print.c
SRCS+=		timevar.c
SRCS+=		argmatch.c
FILES=		README c.m4 glr.c lalr1.cc yacc.c
FILESDIR=	/usr/share/${PROG}
SCRIPTS=	m4sugar.m4
SCRIPTSNAME=	m4sugar.m4
SCRIPTSDIR=	${FILESDIR}/m4sugar
SCRIPTSMODE=	444	
INFOFILES=	bison.info bison.info-1 bison.info-2 bison.info-3 \
		bison.info-4 bison.info-5 bison.info-6 bison.info-7

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}/src ${DIST}/lib ${DIST}/doc ${DIST}/data ${DIST}/data/m4sugar

CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DPKGDATADIR=\"/usr/share/bison\"
CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-I${.CURDIR} -I${DIST}/lib

install:
	for i in ${INFOFILES}; do\
		${INSTALL} -c -o ${INFOOWN} -g ${INFOGRP} -m ${NONBINMODE} ${DIST}/doc/$$i ${DESTDIR}${INFODIR}; \
	done
	
.include <bsd.prog.mk>
