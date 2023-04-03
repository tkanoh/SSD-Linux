#	$ssdlinux: Makefile,v 1.4 2004/06/16 23:04:49 kanoh Exp $

.include <bsd.own.mk>

PROG=		sulogin		
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

FORCE_NO_PAM=	yes
.if ${FULL_SHARED} != "yes"
LDSTATIC=	-static -s
.endif

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

.include <bsd.prog.mk>
