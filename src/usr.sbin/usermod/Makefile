#	$ssdlinux: Makefile,v 1.2 2002/07/29 02:37:46 yamagata Exp $

.include <bsd.own.mk>

PROG=		usermod		
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

USE_PAM=	no

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
