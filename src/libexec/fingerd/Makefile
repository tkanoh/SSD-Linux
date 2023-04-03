#	$ssdlinux: Makefile,v 1.2 2002/06/03 06:48:48 yamagata Exp $
.include <bsd.own.mk>

PROG=		fingerd
MAN=		${PROG}.8

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

.include <bsd.prog.mk>
