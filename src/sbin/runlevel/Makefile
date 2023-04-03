#	$ssdlinux: Makefile,v 1.3 2002/06/06 02:16:37 yamagata Exp $

.include <bsd.own.mk>

PROG=		runlevel
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -I${DIST}/src

.include <bsd.prog.mk>
