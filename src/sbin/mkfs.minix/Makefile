#	$ssdlinux: Makefile,v 1.4 2004/07/08 16:50:46 kanoh Exp $

.include <bsd.own.mk>

PROG=		mkfs.minix
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/disk-utils

LIBULDIR=      ${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

NOGCCERROR=	yes

.include <bsd.prog.mk>
