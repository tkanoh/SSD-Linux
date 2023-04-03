#	$ssdlinux: Makefile,v 1.2 2002/06/06 04:03:41 yamagata Exp $

.include <bsd.own.mk>

PROG=		ipv6tunnel
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/src/miplv6
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

CPPFLAGS+=	-I${.CURDIR}/../../linux/include

.include <bsd.prog.mk>
