#	$ssdlinux: Makefile,v 1.2 2002/06/06 03:21:39 yamagata Exp $

.include <bsd.own.mk>

LIBDHCPDIR=	${.CURDIR}/../../lib/dhcp
.include "${LIBDHCPDIR}/Makefile.cflags"

PROG=		dhcrelay
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/dhcp
.PATH:		${DIST}/relay

CPPFLAGS+=	-I${DIST} -I${DIST}/includes

.include "${LIBDHCPDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
