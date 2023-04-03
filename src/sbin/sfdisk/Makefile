#	$ssdlinux: Makefile,v 1.7 2004/11/05 03:28:06 yamagata Exp $

.include <bsd.own.mk>

PROG=		sfdisk
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/fdisk

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
LDADD+=		${.CURDIR}/../cfdisk/disksize.o
LDADD+=		${.CURDIR}/../cfdisk/i386_sys_types.o
LDADD+=		${.CURDIR}/../fdisk/partname.o

.include <bsd.prog.mk>
