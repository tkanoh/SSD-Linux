#	$ssdlinux: Makefile,v 1.1 2004/08/09 03:22:00 todoroki Exp $

.include <bsd.own.mk>

SCRIPTS=	hotplug
SCRIPTSDIR=	/sbin
SCRIPTSMODE=	755
MAN=		hotplug.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/hotplug
.PATH:		${DIST}/sbin

hotplug.8:
	cp ${DIST}/hotplug.8 ${.CURDIR}/hotplug.8

.include <bsd.prog.mk>

SUBDIR=	etc

.include <bsd.subdir.mk>
