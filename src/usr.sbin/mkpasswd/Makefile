#	$ssdlinux: Makefile,v 1.2 2002/06/06 04:15:26 yamagata Exp $

.include <bsd.own.mk>

PROG=		mkpasswd		
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
