#	$ssdlinux: Makefile,v 1.2 2002/06/06 07:40:07 yamagata Exp $

.include <bsd.own.mk>

PROG=		nslookup
SRCS=		${PROG}.c dighost.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/bind
.PATH:		${DIST}/bin/dig

CPPFLAGS+=	-I${DIST}/bin/dig/include

LIBBINDDIR=	${.CURDIR}/../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
