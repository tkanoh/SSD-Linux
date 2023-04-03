#	$ssdlinux: Makefile,v 1.2 2002/05/31 09:28:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		slattach
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/net-tools
.PATH:		${DIST} ${DIST}/man/en_US

LIBINET6=	${.CURDIR}/../../lib/libinet6
LIBNETTOOL=	${.CURDIR}/../../lib/net-tools
CPPFLAGS+=	-I${LIBNETTOOL} -I${DIST}/include -I${DIST}/lib -I${DIST} 
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBNETTOOL}/Makefile.ldflags"
.include "${LIBINET6}/Makefile.ldflags"

.include <bsd.prog.mk>
