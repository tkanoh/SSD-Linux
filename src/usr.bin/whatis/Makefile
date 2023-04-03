#	$ssdlinux: Makefile,v 1.7 2005/01/11 01:36:15 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	whatis
MAN=		${SCRIPTS}.1
CLEANFILES=	${SCRIPTS} ${MAN} ${MAN}.in

DIST=		${.CURDIR}/../../dist/man
.PATH:		${DIST}/src

whatis: 
	vers=`sed -e s/man-// ${DIST}/version`; \
	sed -e 's,%apropos_or_whatis%,${.TARGET},' \
	    -e "s,%version%,man-$$vers," \
	    -e 's,%manpathoption%,--path,' \
	${DIST}/src/apropos.sh > ${.TARGET}

${MAN}:
	cp ${DIST}/man/en/${SCRIPTS}.man ${.CURDIR}/${.TARGET}.in
	${SHELL} ../man/conf_script ${.CURDIR} ${.TARGET}

.include <bsd.prog.mk>
