#	$ssdlinux: Makefile,v 1.4 2005/03/02 01:44:56 yamagata Exp $

.include <bsd.own.mk>

LIBDHCPDIR=	${.CURDIR}/../../lib/dhcp
.include "${LIBDHCPDIR}/Makefile.cflags"

PROG=		dhcp-svtest
SRCS=		test.c
MKMAN=		no

DIST=		${.CURDIR}/../../dist/dhcp
.PATH:		${DIST}/omapip

CPPFLAGS+=	-I${DIST} -I${DIST}/includes

.include "${LIBDHCPDIR}/Makefile.ldflags"
LDADD+=		${LIBDHCPDIR}/omapip/iscprint.o

.include <bsd.prog.mk>
