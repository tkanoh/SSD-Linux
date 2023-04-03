#	$ssdlinux: Makefile,v 1.5 2002/12/12 08:54:52 yamagata Exp $
#	$NetBSD: Makefile,v 1.8 1997/10/10 09:26:38 lukem Exp $
#	@(#)Makefile	8.1 (Berkeley) 6/6/93

.include <bsd.own.mk>

PROG=		lpc
SRCS=		${PROG}.c cmds.c cmdtab.c
MAN=		${PROG}.8
BINDIR=		/usr/sbin
BINGRP=		daemon
BINMODE=	2555

.include "${.CURDIR}/../Makefile.cflags"

.PATH:		${DIST}/${PROG} ${DIST}/common_source

LDADD=		${.CURDIR}/../common_source/startdaemon.o
LDADD+=		${.CURDIR}/../common_source/common.o
LDADD+=		${.CURDIR}/../common_source/getcap.o

.include <bsd.prog.mk>
