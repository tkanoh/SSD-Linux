#	$ssdlinux: Makefile,v 1.5 2004/08/24 01:03:16 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	version.h
CLEANFILES=	version.h builtins .build

DIST=		${.CURDIR}/../../../dist/bash
.PATH:		${DIST}

version.h:
	${DIST}/support/mkversion.sh -b -S ${DIST} -s release -d ${BASHVERSION} -p 0 -o ${.TARGET}
	rm -f ${.CURDIR}/builtins
	ln -sf ${.CURDIR}/../libbuiltins builtins

proginstall::

scriptsinstall::

.include <bsd.prog.mk>
