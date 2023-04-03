#	$ssdlinux: Makefile,v 1.9 2005/02/25 06:57:55 yamagata Exp $
.include <bsd.own.mk>

PROG=		msgmerge
SRCS=		${PROG}.c plural-count.c
SRCS+=		write-properties.c write-stringtable.c write-po.c msgl-equal.c

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
		${.CURDIR}/../msgcmp/msgl-ascii.o \
		${.CURDIR}/../msgcmp/msgl-iconv.o \
		${.CURDIR}/../msgfmt/plural.o
LDADD+=		${.CURDIR}/../msgfmt/format.o \
		${.CURDIR}/../msgfmt/format-c.o \
		${.CURDIR}/../msgfmt/format-gcc-internal.o \
		${.CURDIR}/../msgfmt/format-python.o \
		${.CURDIR}/../msgfmt/format-lisp.o \
		${.CURDIR}/../msgfmt/format-elisp.o \
		${.CURDIR}/../msgfmt/format-librep.o \
		${.CURDIR}/../msgfmt/format-scheme.o \
		${.CURDIR}/../msgfmt/format-java.o \
		${.CURDIR}/../msgfmt/format-csharp.o \
		${.CURDIR}/../msgfmt/format-awk.o \
		${.CURDIR}/../msgfmt/format-pascal.o \
		${.CURDIR}/../msgfmt/format-perl-brace.o \
		${.CURDIR}/../msgfmt/format-perl.o \
		${.CURDIR}/../msgfmt/format-qt.o \
		${.CURDIR}/../msgfmt/format-ycp.o \
		${.CURDIR}/../msgfmt/format-sh.o \
		${.CURDIR}/../msgfmt/format-tcl.o \
		${.CURDIR}/../msgfmt/format-php.o

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"

.include <bsd.prog.mk>
