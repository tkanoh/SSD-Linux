#	$ssdlinux: Makefile,v 1.2 2002/06/04 07:18:57 yamagata Exp $

.include <bsd.own.mk>

PROG=		writed
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netwrite
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${DIST} -I${DIST}/${PROG} -I${DIST}/include
CPPFLAGS+=	-DBINDIR=\"/usr/bin\"

.include <bsd.prog.mk>
