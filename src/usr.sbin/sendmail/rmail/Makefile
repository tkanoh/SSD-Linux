#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:51:26 yamagata Exp $

.include <bsd.own.mk>

PROG=		rmail
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
