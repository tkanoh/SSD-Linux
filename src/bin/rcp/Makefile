#	$ssdlinux: Makefile,v 1.3 2002/06/05 08:37:46 yamagata Exp $

.include <bsd.own.mk>

PROG=		rcp

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rsh/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR}

.include <bsd.prog.mk>
