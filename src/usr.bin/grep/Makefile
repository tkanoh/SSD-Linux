#	$ssdlinux: Makefile,v 1.8 2004/11/01 08:46:48 yamagata Exp $

.include <bsd.own.mk>

PROG=		grep
SRCS=		grep.c dfa.c kwset.c search.c grepmat.c
SRCS+=		closeout.c error.c exclude.c hard-locale.c isdir.c obstack.c \
		quotearg.c savedir.c xmalloc.c xstrtol.c xstrtoumax.c
SCRIPTS=	egrep fgrep
CLEANFILES=	${SCRIPTS}

DIST=		${.CURDIR}/../../dist/grep
.PATH:		${DIST}/src ${DIST}/lib ${DIST}/doc

CPPFLAGS+=	-DHAVE_CONFIG_H -DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-I${.CURDIR} -I${DIST}/lib

NOGCCERROR=	yes

MLINKS=		grep.1 egrep.1
MLINKS+=	grep.1 fgrep.1

egrep:
	echo '#!/bin/sh' >${.TARGET}
	echo 'exec grep -E $${1+"$$@"}' >>${.TARGET}

fgrep:
	echo '#!/bin/sh' >${.TARGET}
	echo 'exec grep -F $${1+"$$@"}' >>${.TARGET}

.include <bsd.prog.mk>
