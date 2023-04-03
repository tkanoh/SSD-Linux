#	$ssdlinux: Makefile,v 1.3 2002/07/29 02:20:27 yamagata Exp $

.include <bsd.own.mk>

PROG=		lastlog		
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

USE_PAM=	no

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
