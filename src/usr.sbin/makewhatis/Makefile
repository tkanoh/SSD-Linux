#	$ssdlinux: Makefile,v 1.6 2004/07/20 02:24:10 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	makewhatis
MAN=		${SCRIPTS}.8
CLEANFILES=	${SCRIPTS} ${MAN} ${MAN}.in

DIST=		${.CURDIR}/../../dist/man
.PATH:		${DIST}/src

${SCRIPTS}: 
	vers=`sed -e s/man-// ${DIST}/version`; \
	sed -e "s,%version%,man-$$vers," \
	    -e 's,%awk%,/usr/bin/awk,' \
	${DIST}/src/${SCRIPTS}.sh > ${.TARGET}

${MAN}:
	cp ${DIST}/man/en/${SCRIPTS}.man ${.CURDIR}/${.TARGET}.in
	${SHELL} ../../usr.bin/man/conf_script ${.CURDIR} ${.TARGET}

.include <bsd.prog.mk>
