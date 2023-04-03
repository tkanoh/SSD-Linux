#	$ssdlinux: Makefile,v 1.3 2003/06/12 08:52:42 yamagata Exp $

.include <bsd.own.mk>

PROG=		uuxqt
MAN=		${PROG}.8

BINMODE=	4555

DIST=		${.CURDIR}/../../../dist/uucp
.PATH:		${DIST}

LDADD+=		${.CURDIR}/../uucico/log.o \
		${.CURDIR}/../uucico/util.o \
		${.CURDIR}/../uucico/copy.o

.include "${.CURDIR}/../../../lib/uucp/Makefile.cflags"

.include <bsd.prog.mk>
