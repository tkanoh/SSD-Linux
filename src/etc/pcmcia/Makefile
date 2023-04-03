#	$ssdlinux: Makefile,v 1.5 2003/01/09 02:53:47 kanoh Exp $

.include <bsd.own.mk>

SCRIPTS=	config ftl ide ieee1394 memory network parport \
		scsi serial shared wireless
SCRIPTSDIR=	/etc/pcmcia
SCRIPTSMODE=	555

_FILES=		ftl.opts ide.opts ieee1394.opts \
		memory.opts network.opts parport.opts scsi.opts \
		serial.opts wireless.opts 
LOCALFILES=	config.opts
FILESMODE=	444
FILESDIR=	${SCRIPTSDIR}

DIST=		${.CURDIR}/../../dist/pcmcia-cs/etc
.PATH:		${DIST}

filesinstall::
	for file in ${_FILES}; do \
		${INSTALL} -c -m ${FILESMODE} -o ${BINOWN} -g ${BINGRP} ${DIST}/$$file ${DESTDIR}${FILESDIR}; \
	done
	for file in ${LOCALFILES} ; do \
		if [ -f ${.CURDIR}/$$file.${TARGET_SSDHOSTTYPEX} ]; then \
			${INSTALL} -c -m ${FILESMODE} -o ${BINOWN} -g ${BINGRP} \
				${.CURDIR}/$$file.${TARGET_SSDHOSTTYPEX} ${DESTDIR}${FILESDIR}/$$file; \
		else \
			${INSTALL} -c -m ${FILESMODE} -o ${BINOWN} -g ${BINGRP} \
				${DIST}/$$file ${DESTDIR}${FILESDIR}; \
		fi; \
	done

.include <bsd.prog.mk>

SUBDIR=		cis

.include <bsd.subdir.mk>
