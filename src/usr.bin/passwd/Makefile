#	$ssdlinux: Makefile,v 1.3 2004/06/26 11:36:59 kanoh Exp $

.include <bsd.own.mk>

PROG=		passwd		
BINMODE=	4555

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

.include <bsd.prog.mk>
