#	$ssdlinux: Makefile,v 1.2 2002/06/05 06:47:22 yamagata Exp $

.include <bsd.own.mk>

PROG=		tftp
SRCS=		main.c tftp.c tftpsubs.c

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-tftp
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${DIST} -I${DIST}/${PROG} -I${DIST}/include

.include <bsd.prog.mk>
