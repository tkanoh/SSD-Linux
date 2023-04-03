#	$ssdlinux: Makefile,v 1.9 2005/02/25 06:57:35 yamagata Exp $
.include <bsd.own.mk>

PROG=		msgunfmt
SRCS=		${PROG}.c
SRCS+=		read-mo.c read-java.c read-csharp.c read-resources.c read-tcl.c

CPPFLAGS+=	-I${DIST}/gettext/gettext-runtime/intl
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
		${.CURDIR}/../msgcmp/msgl-iconv.o

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"

.include <bsd.prog.mk>
