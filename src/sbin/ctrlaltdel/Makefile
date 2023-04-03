#	$ssdlinux: Makefile,v 1.4 2002/11/27 03:45:14 yamagata Exp $

.include <bsd.own.mk>

PROG=		ctrlaltdel
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/sys-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
LDADD+=		${LIBULDIR}/my_reboot.o

.include <bsd.prog.mk>
