#	$ssdlinux: Makefile,v 1.6 2003/11/10 07:08:55 todoroki Exp $

.include <bsd.own.mk>

PROG=		uucp

BINMODE=	4555
BINOWN=		uucp
BINGRP=		daemon

DIST=		${.CURDIR}/../../../dist/uucp
.PATH:		${DIST}

LDADD+=		${.CURDIR}/../../../libexec/uucp/uucico/log.o \
		${.CURDIR}/../../../libexec/uucp/uucico/util.o \
		${.CURDIR}/../../../libexec/uucp/uucico/copy.o

.include "${.CURDIR}/../../../lib/uucp/Makefile.cflags"

.include <bsd.prog.mk>
