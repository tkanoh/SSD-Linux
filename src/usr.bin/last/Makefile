#	$ssdlinux: Makefile,v 1.4 2002/06/06 09:09:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		last
MAN=		${PROG}.1 lastb.1

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -isystem -I${DIST}/src

SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/lastb

.include <bsd.prog.mk>
