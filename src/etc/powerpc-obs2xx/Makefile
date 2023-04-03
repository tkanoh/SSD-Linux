#	$ssdlinux: Makefile,v 1.2 2004/03/29 09:07:39 todoroki Exp $

.include <bsd.own.mk>

SCRIPTS=	rc shadow rc.reboot rc.shutdown mk.conf
SCRIPTSDIR=	/etc
SCRIPTSMODE=	555

FILES=		inittab passwd securetty
FILESMODE=	444
FILESDIR=	/etc

mk.conf:	mk.conf.in
	sed -e 's/@OPENBLOCKS@/${TARGET_OPENBLOCKS}/g' mk.conf.in > mk.conf

CLEANFILES=	mk.conf

scriptsinstall:
	${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${SCRIPTS} ${DESTDIR}${SCRIPTSDIR}
	chmod 600 ${DESTDIR}${SCRIPTSDIR}/shadow
	chmod 444 ${DESTDIR}${SCRIPTSDIR}/mk.conf

.include <bsd.prog.mk>

SUBDIR=		defaults

.include <bsd.subdir.mk>
