#	$ssdlinux: Makefile,v 1.1 2004/08/09 03:22:00 todoroki Exp $

.include <bsd.own.mk>

_SCRIPTS=	dasd.agent dasd.permissions firmware.agent \
		hotplug.functions ieee1394.agent \
		input.agent input.rc \
		net.agent pci.agent pci.rc scsi.agent \
		tape.agent tape.permissions \
		usb.agent usb.rc
SCRIPTSDIR=	/etc/hotplug
SCRIPTSMODE=	555

_FILES=		blacklist usb.distmap usb.handmap usb.usermap
FILESMODE=	444
FILESDIR=	${SCRIPTSDIR}

DIST=		${.CURDIR}/../../../../dist/hotplug/etc/hotplug
.PATH:		${DIST}

scriptsinstall::
	mkdir -p ${DESTDIR}${SCRIPTSDIR}
	for file in ${_SCRIPTS}; do \
		${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${DIST}/$$file ${DESTDIR}${SCRIPTSDIR}; \
	done

filesinstall::
	mkdir -p ${DESTDIR}${FILESDIR}
	for file in ${_FILES}; do \
		${INSTALL} -c -m ${FILESMODE} -o ${BINOWN} -g ${BINGRP} ${DIST}/$$file ${DESTDIR}${FILESDIR}; \
	done
	mkdir -p ${DESTDIR}${FILESDIR}/{pci,usb}

.include <bsd.prog.mk>
