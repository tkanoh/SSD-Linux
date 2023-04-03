#	$ssdlinux: Makefile,v 1.2 2002/06/05 06:03:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		rwho

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rwho
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

.include <bsd.prog.mk>
