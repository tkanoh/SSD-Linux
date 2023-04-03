#	$ssdlinux: Makefile,v 1.1 2004/08/10 06:56:30 todoroki Exp $

.include <bsd.own.mk>

_FILES=		isl3890
FILESMODE=	444
FILESDIR=	/usr/lib/hotplug/firmware

DIST=		${.CURDIR}
.PATH:		${DIST}

filesinstall::
	mkdir -p ${DESTDIR}${FILESDIR}
	for file in ${_FILES}; do \
		if [ -f ${DIST}/$$file ]; then \
			${INSTALL} -c -m ${FILESMODE} -o ${BINOWN} -g ${BINGRP} ${DIST}/$$file ${DESTDIR}${FILESDIR}; \
		fi; \
	done

.include <bsd.prog.mk>
