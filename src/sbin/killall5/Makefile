#	$ssdlinux: Makefile,v 1.6 2003/04/30 20:13:13 kanoh Exp $

.include <bsd.own.mk>

PROG=		killall5
MAN=		${PROG}.8 pidof.8
LDSTATIC=

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -I${DIST}/src

SYMLINKS+=	${BINDIR}/${PROG} /bin/pidof

.include <bsd.prog.mk>
