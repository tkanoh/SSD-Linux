#	$ssdlinux: Makefile,v 1.3 2002/06/18 03:54:51 yamagata Exp $

.include <bsd.own.mk>

PROG=		rtsol
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/usagi/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}/../../linux/include
LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

.include <bsd.prog.mk>
