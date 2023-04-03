#	$ssdlinux: Makefile,v 1.2 2002/06/05 05:58:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		ruptime

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rwho
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-I${DIST}/${PROG} -I${DIST}/include

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

.include <bsd.prog.mk>
