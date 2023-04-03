#	$ssdlinux: Makefile,v 1.4 2002/11/13 09:58:24 yamagata Exp $

.include	<bsd.own.mk>

PROG=		ping6
SRCS=		${PROG}.c ping_common.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/iputils
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
CPPFLAGS+=	-I${DIST}/include-glibc
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-DHAVE_GETOPT_H=1 -DHAVE_NETINET_IP6_H=1
CPPFLAGS+=	-DHAVE_NETINET_ICMP6_H=1 -DHAVE_GETOPT_LONG=1
CPPFLAGS+=	-DHAVE_CMSG_NXTHDR=1 -DHAVE_INET6_RTHDR_INIT=1
CPPFLAGS+=	-DHAVE_STRUCT_ICMP6_NODEINFO=1
CPPFLAGS+=	-I${DIST}/include

LDADD+=		-lm

.include <bsd.prog.mk>
