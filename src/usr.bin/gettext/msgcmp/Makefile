#	$ssdlinux: Makefile,v 1.8 2005/02/25 07:01:29 yamagata Exp $
.include <bsd.own.mk>

PROG=		msgcmp
SRCS=		${PROG}.c
SRCS+=		message.c po-error.c \
		read-po-abstract.c po-lex.c po-gram-gen.c po-charset.c \
		read-properties.c read-stringtable.c open-po.c dir-list.c str-list.c 
SRCS+=		read-po.c msgl-ascii.c msgl-iconv.c
CLEANFILES=	${.CURDIR}/../include/po-gram-gen2.h

po-lex.o: po-gram-gen2.h
po-gram-gen2.h: po-gram-gen.h
	sed -e 's/[yY][yY]/po_gram_/g' ${DIST}/gettext/src/po-gram-gen.h > ${.CURDIR}/../include/${.TARGET}

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"

.include <bsd.prog.mk>
