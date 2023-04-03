#	$ssdlinux: Makefile,v 1.2 2002/06/12 03:14:58 yamagata Exp $

.include <bsd.own.mk>

PROG=		ifconfig
MKMAN=		no

LDSTATIC=	-static

DIST=		${.CURDIR}/../../../dist/usagi-tool/src/net-tools
.PATH:		${DIST} ${DIST}/man/en_US

LIBNETDIR=	${.CURDIR}/../../../lib/net-tools
LDDIR!=		cd ${LIBNETDIR} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lnet-tools
DPADD+=		${LIBNETDIR}/libnet-tools.a
#LDADD+=	-L/usr/inet6/lib -linet6
#DPADD+=	/usr/inet6/lib/libinet6.a

CPPFLAGS+=	-I${LIBNETDIR}
CPPFLAGS+=	-I${DIST} -I${DIST}/include -I${DIST}/lib
CPPFLAGS+=	-DNET_TOOL_LIB_INSTALLER
CPPFLAGS+=	-DNO_USAGE

proginstall:

.include <bsd.prog.mk>
