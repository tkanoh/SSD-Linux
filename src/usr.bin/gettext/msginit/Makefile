#	$ssdlinux: Makefile,v 1.7 2005/02/25 06:58:21 yamagata Exp $
.include <bsd.own.mk>

PROG=		msginit
SRCS=		${PROG}.c localealias.c
SRCS+=		localename.c

CLEANFILES=	libgnuintl.h

CPPFLAGS+=	-I${.CURDIR}
LDADD+=		${.CURDIR}/../msgmerge/plural-count.o
LDADD+=		${.CURDIR}/../msgcmp/message.o \
		${.CURDIR}/../msgcmp/po-error.o \
		${.CURDIR}/../msgcmp/read-po-abstract.o \
		${.CURDIR}/../msgcmp/po-lex.o \
		${.CURDIR}/../msgcmp/po-gram-gen.o \
		${.CURDIR}/../msgcmp/po-charset.o \
		${.CURDIR}/../msgcmp/read-properties.o \
		${.CURDIR}/../msgcmp/read-stringtable.o \
		${.CURDIR}/../msgcmp/open-po.o \
		${.CURDIR}/../msgcmp/dir-list.o \
		${.CURDIR}/../msgcmp/str-list.o
LDADD+=		${.CURDIR}/../msgcmp/read-po.o \
		${.CURDIR}/../msgmerge/write-properties.o \
		${.CURDIR}/../msgmerge/write-stringtable.o \
		${.CURDIR}/../msgmerge/write-po.o \
		${.CURDIR}/../msgcmp/msgl-ascii.o \
		${.CURDIR}/../msgcmp/msgl-iconv.o \
		${.CURDIR}/../msgen/msgl-english.o \
		${.CURDIR}/../xgettext/po-time.o \
		${.CURDIR}/../msgfmt/plural.o \
		${.CURDIR}/../msgfmt/plural-table.o

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"

.PATH:	${DIST}/gettext/gettext-runtime/intl

localealias.c: libgnuintl.h

libgnuintl.h:
	sed -e 's,@''HAVE_POSIX_PRINTF''@,1,g' \
	    -e 's,@''HAVE_ASPRINTF''@,1,g' \
	    -e 's,@''HAVE_SNPRINTF''@,1,g' \
	    -e 's,@''HAVE_WPRINTF''@,0,g' \
		${DIST}/gettext/gettext-runtime/intl/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
