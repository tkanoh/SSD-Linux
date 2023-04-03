#	$ssdlinux: Makefile,v 1.4 2002/07/02 01:31:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		flex
SRCS=		ccl.c dfa.c ecs.c gen.c main.c misc.c nfa.c parse.c scan.c \
		skel.c sym.c tblcmp.c yylex.c
CLEANFILES=	parse.c parse.h scan.c

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS=	-DHAVE_CONFIG_H -I${.CURDIR} -I${DIST}

SYMLINKS=	${BINDIR}/${PROG} ${BINDIR}/${PROG}++
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/lex

parse.c: parse.y
	bison -y -d ${DIST}/parse.y
	@sed '/extern char.*malloc/d' <y.tab.c >parse.tmp
	@mv parse.tmp ${.TARGET}
	@mv y.tab.h parse.h
	@rm -f y.tab.c

scan.c: scan.l
	flex -t -p ${DIST}/scan.l >${.TARGET}
	@sed s,\"${DIST}/scan.l\",\"scan.l\", <${.TARGET} >scan.tmp
	@mv scan.tmp ${.TARGET}

.include <bsd.prog.mk>
