#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:08:51 yamagata Exp $

.include <bsd.own.mk>

PROG=		postconf
SRCS=		dummy.c ${PROG}.c

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man1

CPPFLAGS+=	-I${.CURDIR}

CLEANFILES=	dummy.c bool_table.h int_table.h raw_table.h \
		str_table.h time_table.h bool_vars.h int_vars.h \
		raw_vars.h str_vars.h time_vars.h

dummy.c:
	awk -f ${DIST}/src/${PROG}/extract.awk ${DIST}/src/${PROG}/../*/*.c
	touch dummy.c

.include <bsd.prog.mk>
