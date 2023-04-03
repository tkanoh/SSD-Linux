#	$ssdlinux: Makefile,v 1.2 2002/06/05 03:31:30 yamagata Exp $

.include <bsd.own.mk>

PROG=		mesg

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -I${DIST}/src

.include <bsd.prog.mk>
