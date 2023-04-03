#	$ssdlinux: Makefile,v 1.3 2002/10/08 03:01:24 yamagata Exp $

.include <bsd.own.mk>

PROG=		uupick
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/uucp
.PATH:		${DIST}

LDADD+=		${.CURDIR}/../../../libexec/uucp/uucico/log.o \
		${.CURDIR}/../../../libexec/uucp/uucico/copy.o

.include "${.CURDIR}/../../../lib/uucp/Makefile.cflags"

.include <bsd.prog.mk>
