#	$ssdlinux: Makefile,v 1.1 2004/08/09 03:22:00 todoroki Exp $

.include <bsd.own.mk>

SCRIPTS=	rc.hotplug
SCRIPTSDIR=	/etc
SCRIPTSMODE=	555
CLEANFILES=	rc.hotplug

DIST=		${.CURDIR}/../../../dist/hotplug

rc.hotplug:
	cp ${DIST}/etc/rc.d/init.d/hotplug ${.CURDIR}/rc.hotplug

scriptsinstall:
	${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${SCRIPTS} ${DESTDIR}${SCRIPTSDIR}

.include <bsd.prog.mk>

SUBDIR=	hotplug hotplug.d

.include <bsd.subdir.mk>

