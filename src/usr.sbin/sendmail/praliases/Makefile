#	$ssdlinux: Makefile,v 1.4 2004/07/04 07:09:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		praliases
BINOWN=		bin
BINGRP=		bin
BINMODE=	555
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-DNOT_SENDMAIL
CPPFLAGS+=	-I${DIST}/${PROG} -I${DIST}/sendmail
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../../lib/libdb
.endif

.include <bsd.prog.mk>
