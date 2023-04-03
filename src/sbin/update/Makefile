#	$ssdlinux: Makefile,v 1.2 2002/05/31 09:36:09 yamagata Exp $

.include <bsd.own.mk>

PROG=		update
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/updated
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST} -fomit-frame-pointer -Wall

.include <bsd.prog.mk>
