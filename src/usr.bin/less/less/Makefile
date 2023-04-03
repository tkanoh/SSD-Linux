#	$ssdlinux: Makefile,v 1.5 2004/07/04 05:53:16 yamagata Exp $

.include <bsd.own.mk>

PROG=		less
SRCS=		main.c screen.c brac.c ch.c charset.c cmdbuf.c command.c \
		decode.c edit.c filename.c forwback.c help.c ifile.c input.c \
		jump.c line.c linenum.c lsystem.c mark.c optfunc.c option.c \
		opttbl.c os.c output.c position.c prompt.c search.c signal.c \
		tags.c ttyin.c version.c
CLEANFILES=	${PROG}.1

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS=	-DBINDIR=\"/usr/bin\"
CPPFLAGS+=	-DSYSDIR=\"/usr/bin\"
CPPFLAGS+=	-I${.CURDIR}
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${DIST}/../ncurses/include
.endif

LDADD+=		-L${DIST}/../../lib/libncurses/build/lib -lncurses

${PROG}.1: ${DIST}/${PROG}.nro
	cat ${DIST}/${PROG}.nro > ${.TARGET}

.include <bsd.prog.mk>
