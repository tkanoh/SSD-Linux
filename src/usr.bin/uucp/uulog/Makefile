#	$ssdlinux: Makefile,v 1.6 2003/11/10 07:08:55 todoroki Exp $

.include <bsd.own.mk>

PROG=		uulog
MKMAN=		no

BINMODE=	4555
BINOWN=		uucp
BINGRP=		daemon

DIST=		${.CURDIR}/../../../dist/uucp
.PATH:		${DIST}

LDADD+=		${.CURDIR}/../../../libexec/uucp/uucico/log.o

.include "${.CURDIR}/../../../lib/uucp/Makefile.cflags"

.include <bsd.prog.mk>
