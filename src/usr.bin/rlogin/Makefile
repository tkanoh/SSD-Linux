#	$ssdlinux: Makefile,v 1.2 2002/06/05 05:47:31 yamagata Exp $

.include <bsd.own.mk>

PROG=		rlogin

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rsh/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR}/../../bin/rcp

.include <bsd.prog.mk>
