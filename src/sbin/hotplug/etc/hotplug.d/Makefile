#	$ssdlinux: Makefile,v 1.1 2004/08/09 03:22:00 todoroki Exp $

.include <bsd.own.mk>

_SCRIPTS=	default.hotplug
SCRIPTSDIR=	/etc/hotplug.d/default
SCRIPTSMODE=	555

DIST=		${.CURDIR}/../../../../dist/hotplug/etc/hotplug.d/default
.PATH:		${DIST}

scriptsinstall::
	mkdir -p ${DESTDIR}${SCRIPTSDIR}
	for file in ${_SCRIPTS}; do \
		${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${DIST}/$$file ${DESTDIR}${SCRIPTSDIR}; \
	done

.include <bsd.prog.mk>
