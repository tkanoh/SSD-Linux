#	$ssdlinux: Makefile,v 1.7 2005/02/25 06:58:50 yamagata Exp $
.include <bsd.own.mk>

PROG=		msggrep

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
		${.CURDIR}/../msgfilter/msgl-charset.o
LDADD+=		-L${.CURDIR}/../libgrep -lgrep
DPADD+=		${.CURDIR}/../libgrep/libgrep.a

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"
.PATH:		${DIST}/gettext/gettext-tools/libgrep
CPPFLAGS+=	-I${DIST}/gettext/gettext-tools/libgrep

.include <bsd.prog.mk>
