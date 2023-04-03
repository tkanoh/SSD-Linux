#	$ssdlinux: Makefile,v 1.3 2004/02/25 07:38:24 yamagata Exp $

.include <bsd.own.mk>

PROG=		vipw
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

LINKS=         ${BINDIR}/${PROG} ${BINDIR}/vigr

NOGCCERROR=	yes

.include <bsd.prog.mk>
