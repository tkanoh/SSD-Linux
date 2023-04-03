#	$ssdlinux: Makefile,v 1.3 2002/06/11 08:08:24 kanoh Exp $

.include <bsd.own.mk>

PROG=		mail.local
BINDIR=		/usr/libexec
BINOWN=		root
BINGRP=		smmsp
BINMODE=	4555
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
