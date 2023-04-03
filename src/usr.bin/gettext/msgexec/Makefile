#	$ssdlinux: Makefile,v 1.7 2005/02/25 07:00:19 yamagata Exp $
.include <bsd.own.mk>

PROG=		msgexec

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
		${.CURDIR}/../msgcmp/msgl-ascii.o

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"

.include <bsd.prog.mk>
