#	$ssdlinux: Makefile,v 1.3 2002/11/13 09:44:30 yamagata Exp $

.include <bsd.own.mk>

PROG=		traceroute6
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/src/iputils
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
CPPFLAGS+=	-I${DIST}/include-glibc
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
