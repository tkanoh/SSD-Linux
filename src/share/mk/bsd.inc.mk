#	$ssdlinux: bsd.inc.mk,v 1.1.1.1 2002/05/02 13:37:09 kanoh Exp $
#	$NetBSD: bsd.inc.mk,v 1.16 2000/06/06 09:53:29 mycroft Exp $

.PHONY:		incinstall
includes:	${INCS} incinstall

.if defined(INCS)
incinstall:: ${INCS:@I@${DESTDIR}${INCSDIR}/$I@}
.PRECIOUS: ${INCS:@I@${DESTDIR}${INCSDIR}/$I@}
.if !defined(UPDATE)
.PHONY: ${INCS:@I@${DESTDIR}${INCSDIR}/$I@}
.endif

__incinstall: .USE
	@cmp -s ${.ALLSRC} ${.TARGET} > /dev/null 2>&1 || \
	    (echo "${INSTALL} ${RENAME} ${PRESERVE} ${INSTPRIV} -c \
		-o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} ${.ALLSRC} \
		${.TARGET}" && \
	     ${INSTALL} ${RENAME} ${PRESERVE} ${INSTPRIV} -c -o ${BINOWN} \
		 -g ${BINGRP} -m ${NONBINMODE} ${.ALLSRC} ${.TARGET})

.for I in ${INCS:O:u}
${DESTDIR}${INCSDIR}/$I: $I __incinstall
.endfor
.endif

.if !target(incinstall)
incinstall::
.endif
