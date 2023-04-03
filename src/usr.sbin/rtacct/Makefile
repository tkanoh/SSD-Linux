#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:30:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		rtacct
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/src/iproute2/ip
.PATH:		${DIST}

LIBIPROUTE2=	${.CURDIR}/../../lib/iproute2
.include "${LIBIPROUTE2}/Makefile.cflags"
.include "${LIBIPROUTE2}/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
