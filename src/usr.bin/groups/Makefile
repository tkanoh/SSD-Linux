#	$ssdlinux: Makefile,v 1.2 2002/06/05 02:20:05 yamagata Exp $

.include <bsd.own.mk>

PROG=		groups		

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
