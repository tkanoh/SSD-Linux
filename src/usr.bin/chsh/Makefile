#	$ssdlinux: Makefile,v 1.2 2002/06/04 09:30:53 yamagata Exp $

.include <bsd.own.mk>

PROG=		chsh		
BINMODE=	4555

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
