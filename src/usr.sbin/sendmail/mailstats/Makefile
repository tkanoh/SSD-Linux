#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:51:26 yamagata Exp $

.include <bsd.own.mk>

PROG=		mailstats
BINOWN=		bin
BINGRP=		bin
BINMODE=	555
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-DNOT_SENDMAIL
CPPFLAGS+=	-I${DIST}/${PROG} -I${DIST}/sendmail

.include <bsd.prog.mk>
