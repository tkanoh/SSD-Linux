#	$ssdlinux: Makefile,v 1.3 2002/12/12 08:54:52 yamagata Exp $
#	$NetBSD: Makefile,v 1.7 1997/10/10 09:26:40 lukem Exp $
#	@(#)Makefile	8.1 (Berkeley) 6/6/93

.include <bsd.own.mk>

PROG=		lpq
BINOWN=		root
BINGRP=		daemon
BINMODE=	6555
BINDIR=		/usr/bin

.include "${.CURDIR}/../Makefile.cflags"

.PATH:		${DIST}/${PROG}

LDADD=		${.CURDIR}/../common_source/displayq.o
LDADD+=		${.CURDIR}/../common_source/common.o
LDADD+=		${.CURDIR}/../common_source/getcap.o

.include <bsd.prog.mk>
