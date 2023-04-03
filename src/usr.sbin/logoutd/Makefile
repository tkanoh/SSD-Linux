#	$ssdlinux: Makefile,v 1.2 2002/06/06 04:10:34 yamagata Exp $

.include <bsd.own.mk>

PROG=		logoutd		
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
