#	$ssdlinux: Makefile,v 1.2 2002/07/12 07:24:07 kanoh Exp $

.include <bsd.own.mk>

SCRIPTS=	rc shadow rc.shutdown rc.reboot
SCRIPTSDIR=	/etc
SCRIPTSMODE=	555

FILES=		inittab mk.conf passwd securetty
FILESMODE=	444
FILESDIR=	/etc

scriptsinstall:
	${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${SCRIPTS} ${DESTDIR}${SCRIPTSDIR}
	chmod 600 ${DESTDIR}${SCRIPTSDIR}/shadow

.include <bsd.prog.mk>

SUBDIR=		defaults

.include <bsd.subdir.mk>
