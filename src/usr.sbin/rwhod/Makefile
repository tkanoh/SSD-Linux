#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:34:24 yamagata Exp $

.include <bsd.own.mk>

PROG=		rwhod
SRCS=		${PROG}.c daemon.c
MAN=		${PROG}.8 daemon.3

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rwho
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"
 
CPPFLAGS+=	-DHAVE_GETIFADDRS=1 -DHAVE_IFADDRS_H=1
CPPFLAGS+=	-I${.CURDIR}

NOGCCERROR=	yes

.include <bsd.prog.mk>
