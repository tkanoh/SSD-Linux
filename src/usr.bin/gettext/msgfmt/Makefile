#	$ssdlinux: Makefile,v 1.9 2005/02/25 06:59:30 yamagata Exp $
.include <bsd.own.mk>

PROG=		msgfmt
SRCS=		${PROG}.c
SRCS+=		write-mo.c write-java.c write-csharp.c write-resources.c \
		write-tcl.c write-qt.c plural-eval.c
SRCS+=		plural.c plural-table.c
SRCS+=		format.c \
		format-c.c format-sh.c format-python.c format-lisp.c format-elisp.c \
		format-librep.c format-scheme.c format-java.c format-csharp.c format-awk.c format-pascal.c \
		format-ycp.c format-tcl.c format-perl.c format-perl-brace.c format-php.c \
		format-gcc-internal.c format-qt.c

CPPFLAGS+=	-I${DIST}/gettext/gettext-runtime/intl
LDADD+=  	${.CURDIR}/../msgcmp/message.o \
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
LDADD+= 	${.CURDIR}/../msgcmp/read-po.o \
		${.CURDIR}/../msgcmp/msgl-ascii.o \
		${.CURDIR}/../msgcmp/msgl-iconv.o

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"

.include <bsd.prog.mk>
