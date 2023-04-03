#	$ssdlinux: Makefile,v 1.5 2002/10/01 03:30:22 yamagata Exp $

.include <bsd.own.mk>

PROG=		diff
SRCS=		analyze.c context.c ${PROG}.c dir.c ed.c ifdef.c io.c \
		normal.c side.c util.c basename.c exclude.c fnmatch.c \
		posixver.c quotesys.c regex.c strftime.c

DIST=		${.CURDIR}/../../dist/diffutils
.PATH:		${DIST}/lib ${DIST}/src ${DIST}/man

CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-DHAVE_CONFIG_H -DPR_PROGRAM=\"/usr/bin/pr\"
CPPFLAGS+=	-I${.CURDIR}/../cmp -I${DIST}/lib -I${.CURDIR}
LDADD+=		${.CURDIR}/../cmp/version.o \
		${.CURDIR}/../cmp/c-stack.o \
		${.CURDIR}/../cmp/cmpbuf.o \
		${.CURDIR}/../cmp/exitfail.o \
		${.CURDIR}/../cmp/freesoft.o \
		${.CURDIR}/../cmp/getopt.o \
		${.CURDIR}/../cmp/getopt1.o \
		${.CURDIR}/../cmp/hard-locale.o \
		${.CURDIR}/../cmp/xmalloc.o

CLEANFILES=	regex.h

NOGCCERROR=	yes

regex.c: regex.h

regex.h:
	cat ${DIST}/lib/regex.hin > ${.TARGET}

.include <bsd.prog.mk>
