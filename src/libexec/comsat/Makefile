#	$ssdlinux: Makefile,v 1.2 2002/06/03 06:46:54 yamagata Exp $

.include <bsd.own.mk>

PROG=		comsat
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/biff+comsat/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR}

.include <bsd.prog.mk>
