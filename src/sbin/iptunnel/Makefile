#	$ssdlinux: Makefile,v 1.2 2002/06/06 01:43:10 yamagata Exp $

.include <bsd.own.mk>

PROG=		iptunnel
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/src/net-tools
.PATH:		${DIST} ${DIST}/man/en_US

LIBINET6=	${.CURDIR}/../../lib/libinet6
LIBNETTOOL=	${.CURDIR}/../../lib/net-tools
CPPFLAGS+=	-I${LIBNETTOOL} -I${DIST}/include -I${DIST}/lib -I${DIST} 
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBNETTOOL}/Makefile.ldflags"
.include "${LIBINET6}/Makefile.ldflags"

.include <bsd.prog.mk>
