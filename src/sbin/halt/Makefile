#	$ssdlinux: Makefile,v 1.6 2004/06/16 22:23:58 kanoh Exp $

.include <bsd.own.mk>

PROG=		halt
SRCS=		${PROG}.c ifdown.c hddown.c utmp.c
MAN=		${PROG}.8 poweroff.8 reboot.8

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE
NOGCCERROR=	yes

SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/poweroff
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/reboot

.include <bsd.prog.mk>
