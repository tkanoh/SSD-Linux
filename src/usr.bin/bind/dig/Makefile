#	$ssdlinux: Makefile,v 1.2 2002/06/06 07:39:08 yamagata Exp $

.include <bsd.own.mk>

PROG=		dig
SRCS=		${PROG}.c dighost.c

FILES=		isc-config.sh
FILESMODE=	555

DIST=		${.CURDIR}/../../../dist/bind
.PATH:		${DIST}/bin/dig

CPPFLAGS+=	-I${DIST}/bin/dig/include

LIBBINDDIR=	${.CURDIR}/../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
