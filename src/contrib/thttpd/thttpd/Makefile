#	$ssdlinux: Makefile,v 1.6 2004/06/08 01:23:41 yamagata Exp $

.include <bsd.own.mk>

PROG=		thttpd
SRCS=		${PROG}.c libhttpd.c fdwatch.c mmc.c timers.c \
		match.c tdate_parse.c
FILES=		syslogtocern
FILESMODE=	${BINMODE}
MAN=		${PROG}.8 ${FILES}.8
CLEANFILES=	mime_encodings.h mime_types.h
	
THTTPDTOP=	${.CURDIR}/..
DIST=           ${.CURDIR}/../../../dist/thttpd
.PATH:		${DIST} ${DIST}/extras

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

libhttpd.o: mime_encodings.h mime_types.h
mime_encodings.h:
	sed < ${DIST}/mime_encodings.txt > ${.TARGET} \
		-e 's/#.*//' -e 's/[	]*$$//' -e '/^$$/d' \
		-e 's/[	][	]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'

mime_types.h:
	sed < ${DIST}/mime_types.txt > ${.TARGET} \
		-e 's/#.*//' -e 's/[	]*$$//' -e '/^$$/d' \
		-e 's/[	][	]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'

.include <bsd.prog.mk>
