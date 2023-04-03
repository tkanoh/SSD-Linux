#	$ssdlinux: Makefile,v 1.1 2003/04/07 05:28:40 kanoh Exp $

.include <bsd.own.mk>

SCRIPTS=	rc shadow rc.reboot rc.shutdown
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
