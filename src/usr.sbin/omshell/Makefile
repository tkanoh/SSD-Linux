#	$ssdlinux: Makefile,v 1.2 2002/06/04 06:19:04 yamagata Exp $

.include <bsd.own.mk>

LIBDHCPDIR=	${.CURDIR}/../../lib/dhcp
.include "${LIBDHCPDIR}/Makefile.cflags"

PROG=		omshell

DIST=		${.CURDIR}/../../dist/dhcp
.PATH:		${DIST}/dhcpctl

CPPFLAGS+=	-I${DIST} -I${DIST}/includes

LDADD+=		-L${LIBDHCPDIR}/dhcpctl -ldhcpctl 
DPADD+=		${LIBDHCPDIR}/dhcpctl/libdhcpctl.a
.include "${LIBDHCPDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
