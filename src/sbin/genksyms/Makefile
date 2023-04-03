#	$ssdlinux: Makefile,v 1.7 2004/06/16 23:04:49 kanoh Exp $

.include <bsd.own.mk>

PROG=		genksyms
SRCS=		${PROG}.c parse.c lex.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/modutils
.PATH:		${DIST}/${PROG} ${DIST}/man

.include "${.CURDIR}/../../lib/modutils/Makefile.cflags"

CPPFLAGS+=	-I${.CURDIR} -I${DIST}/${PROG}
CPPFLAGS+=	-Wno-uninitialized

LDADD+=		-L${LIBMODU}/libutil -lutil
LDADD+=		-L${LIBMODU}/../libz -lz
DPADD+=		${LIBMODU}/libutil/libutil.a

CLEANFILES=	crc32.tab lex.c makecrc32 parse.c parse.h parse.output \
		keywords.c

parse.c: crc32.tab
	bison -o ${.TARGET} -dtv ${DIST}/${PROG}/parse.y

lex.c:
	flex -o${.TARGET} -d ${DIST}/${PROG}/lex.l parse.h

crc32.tab: ${DIST}/${PROG}/makecrc32.c
	${HOST_CC} -O -Werror -I. -I${DIST}/${PROG} -o makecrc32 ${DIST}/${PROG}/makecrc32.c
	./makecrc32 > ${.TARGET}.tmp
	mv crc32.tab.tmp ${.TARGET}

keywords.c: ${DIST}/${PROG}/keywords.gperf ${DIST}/${PROG}/keywords.gperf_shipped ${DIST}/${PROG}/keywords.c_shipped
	@cmp ${DIST}/${PROG}/keywords.gperf_shipped ${DIST}/${PROG}/keywords.gperf && \
	  cp ${DIST}/${PROG}/keywords.c_shipped ${.TARGET} || \
	  (set -ex; \
	   gperf -a -C -E -g -H is_reserved_hash -k 1,3,$$ -N is_reserved_word -p -t ${DIST}/${PROG}/keywords.gperf > ${.TARGET}.tmp ; \
	   rm -f ${.TARGET}; \
	   sed -e '/Command-line/s/[^ ]*keywords.gperf/keywords.gperf/' ${.TARGET}.tmp >${.TARGET}; \
	   rm ${.TARGET}.tmp; \
	   cp -f ${DIST}/${PROG}/keywords.gperf ${DIST}/${PROG}/keywords.gperf_shipped; \
	   cp -f ${.TARGET} ${DIST}/${PROG}/keywords.c_shipped; \
	  )

genksyms.o: crc32.tab
lex.o: keywords.c

.include <bsd.prog.mk>
