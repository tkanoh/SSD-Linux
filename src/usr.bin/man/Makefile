#	$ssdlinux: Makefile,v 1.8 2004/08/23 06:55:34 yamagata Exp $

.include <bsd.own.mk>

PROG=		man
SRCS=		msg.c man.c manfile.c manpath.c man-config.c man-getopt.c \
		man-iconv.c to_cat.c different.c gripes.c glob.c util.c
MAN=		${PROG}.1 man.conf.5
CLEANFILES=	${MAN} man.conf man.conf.man man.1.in man.conf.5.in \
		paths.h version.h gripedefs.h msg.c makemsg

DIST=		${.CURDIR}/../../dist/man
.PATH:		${DIST}/src

CPPFLAGS=	-Wall -I${DIST}/src -I. \
		-DSTDC_HEADERS -DPOSIX -DDO_COMPRESS
LDFLAGS=	-s

NOGCCERROR=	yes

msg.c: makemsg paths.h version.h
	./makemsg ${DIST}/msgs/mess.en gripedefs.h ${.TARGET}

paths.h: conf_script
	${SHELL} ./conf_script ${DIST}/src ${.TARGET}

version.h:
	vers=`sed -e s/man-// ${DIST}/version`; \
	echo "static char version[] = \"$$vers\";" > ${.TARGET}

makemsg: makemsg.c
	${HOST_CC} -O -s ${DIST}/src/${.TARGET}.c -o ${.TARGET}

man.conf: conf_script
	${SHELL} ./conf_script ${DIST}/src ${.TARGET}

man.1: conf_script
	cp ${DIST}/man/en/man.man ${.CURDIR}/${.TARGET}.in
	${SHELL} ./conf_script ${.CURDIR} ${.TARGET}

man.conf.5: conf_script
	cp ${DIST}/man/en/man.conf.man ${.CURDIR}/${.TARGET}.in
	${SHELL} ./conf_script ${.CURDIR} ${.TARGET}

.include <bsd.prog.mk>
