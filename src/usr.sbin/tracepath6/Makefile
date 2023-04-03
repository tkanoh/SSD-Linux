#	$ssdlinux: Makefile,v 1.5 2002/11/13 09:43:00 yamagata Exp $

.include <bsd.own.mk>

PROG=		tracepath6
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/usagi-tool/src/iputils
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
CPPFLAGS+=	-I${DIST}/include-glibc
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-DHAVE_CMSG_NXTHDR=1 -DHAVE_IPV6_RECVERR_IN_NETINET_IN_H=1

${MAN}:
	cp ${DIST}/tracepath.8 ${.TARGET}

.include <bsd.prog.mk>
