#	$ssdlinux: Makefile,v 1.8 2004/06/16 22:25:02 kanoh Exp $

.include <bsd.own.mk>

PROG=		shutdown
SRCS=		dowall.c utmp.c ${PROG}.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -isystem -I${DIST}/src
NOGCCERROR=	yes

.include <bsd.prog.mk>
