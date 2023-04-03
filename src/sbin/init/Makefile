#	$ssdlinux: Makefile,v 1.8 2004/06/16 22:22:33 kanoh Exp $

.include <bsd.own.mk>

PROG=		init
SRCS=		${PROG}.c utmp.c
MAN=		${PROG}.8 telinit.8 initscript.5 inittab.5 rc.conf.5

INCS=		initreq.h
INCSDIR=	/usr/include

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -DINIT_MAIN -isystem -I${DIST}/src
NOGCCERROR=	yes

SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/telinit

.include <bsd.prog.mk>
