#	$ssdlinux: bsd.nls.mk,v 1.1.1.1 2002/05/02 13:37:09 kanoh Exp $
#	$NetBSD: bsd.nls.mk,v 1.27 2001/05/08 03:19:52 sommerfeld Exp $

.if !target(__initialized__)
__initialized__:
.if exists(${.CURDIR}/../Makefile.inc)
.include "${.CURDIR}/../Makefile.inc"
.endif
.MAIN:		all
.endif

.PHONY:		cleannls nlsinstall
cleandir: cleannls

.SUFFIXES: .cat .msg

.msg.cat:
	@rm -f ${.TARGET}
	gencat ${.TARGET} ${.IMPSRC}

.if defined(NLS) && !empty(NLS)
NLSALL= ${NLS:.msg=.cat}
.NOPATH: ${NLSALL}

NLSNAME?=${PROG:Ulib${LIB}}

.if ${MKNLS} != "no"
realinstall: nlsinstall
realall: ${NLSALL}
.endif

cleannls:
	rm -f ${NLSALL}

nlsinstall:: ${DESTDIR}${NLSDIR}
.PRECIOUS:: ${DESTDIR}${NLSDIR}
.PHONY:: ${DESTDIR}${NLSDIR}

${DESTDIR}${NLSDIR}:
	@if [ ! -d ${.TARGET} ] || [ -h ${.TARGET} ] ; then \
		echo creating ${.TARGET}; \
		/bin/rm -rf ${.TARGET}; \
		${INSTALL} ${INSTPRIV} -d -o ${NLSOWN} -g ${NLSGRP} -m 755 \
		    ${.TARGET}; \
	fi

nlsinstall:: ${NLSALL:@F@${DESTDIR}${NLSDIR}/${F:T:R}/${NLSNAME}.cat@}
.PRECIOUS: ${NLSALL:@F@${DESTDIR}${NLSDIR}/${F:T:R}/${NLSNAME}.cat@}
.if !defined(UPDATE)
.PHONY: ${NLSALL:@F@${DESTDIR}${NLSDIR}/${F:T:R}/${NLSNAME}.cat@}
.endif

__nlsinstall: .USE
	${INSTALL} ${INSTPRIV} -d -o ${NLSOWN} -g ${NLSGRP} ${.TARGET:H}
	${INSTALL} ${RENAME} ${PRESERVE} ${COPY} ${INSTPRIV} -o ${NLSOWN} \
	    -g ${NLSGRP} -m ${NLSMODE} ${.ALLSRC} ${.TARGET}

.for F in ${NLSALL:O:u}
.if !defined(BUILD) && !make(all) && !make(${F})
${DESTDIR}${NLSDIR}/${F:T:R}/${NLSNAME}.cat: .MADE
.endif
${DESTDIR}${NLSDIR}/${F:T:R}/${NLSNAME}.cat: ${F} __nlsinstall
.endfor
.else
cleannls:
.endif
