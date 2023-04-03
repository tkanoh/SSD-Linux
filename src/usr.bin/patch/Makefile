#	$ssdlinux: Makefile,v 1.4 2002/07/05 06:59:35 yamagata Exp $

.include <bsd.own.mk>

PROG=		patch
LIBSRCS=	getopt.c getopt1.c malloc.c memchr.c realloc.c rename.c
SRCS=		 addext.c argmatch.c backupfile.c basename.c error.c inp.c \
		maketime.c mkdir.c partime.c patch.c pch.c quotearg.c \
		quotesys.c rmdir.c util.c version.c xmalloc.c ${LIBSRCS}
MAN=		${PROG}.1
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS=	-DHAVE_CONFIG_H -D_GNU_SOURCE -Ded_PROGRAM=\"/bin/ed\"
CPPFLAGS+=	-I${.CURDIR} -I${DIST}

${MAN}:
	cat ${DIST}/patch.man > ${.TARGET}

.include <bsd.prog.mk>
