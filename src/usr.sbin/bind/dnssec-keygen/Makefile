#	$ssdlinux: Makefile,v 1.2 2002/06/06 02:46:36 yamagata Exp $

.include <bsd.own.mk>

PROG=		dnssec-keygen
SRCS=		${PROG}.c dnssectool.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/bind
.PATH:		${DIST}/bin/dnssec

LIBBINDDIR=	${.CURDIR}/../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
