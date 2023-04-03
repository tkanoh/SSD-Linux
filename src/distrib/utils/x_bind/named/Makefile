#	$ssdlinux: Makefile,v 1.2 2005/03/14 03:44:34 yamagata Exp $

.include <bsd.own.mk>

PROG=		named
SRCS=		aclconf.c client.c config.c control.c controlconf.c interfacemgr.c \
		listenlist.c log.c logconf.c main.c notify.c \
		query.c server.c sortlist.c \
		tkeyconf.c tsigconf.c update.c xfrout.c \
		zoneconf.c \
		lwaddr.c lwresd.c lwdclient.c lwderror.c lwdgabn.c \
		lwdgnba.c lwdgrbn.c lwdnoop.c lwsearch.c \
		os.c
MKMAN=		no
NO_SSL=		yes

DIST=		${.CURDIR}/../../../../dist/bind
.PATH:		${DIST}/bin/${PROG} ${DIST}/bin/${PROG}/unix

CPPFLAGS+=	-I${DIST}/bin/${PROG}/include
CPPFLAGS+=	-I${DIST}/bin/${PROG}/unix/include
CPPFLAGS+=	-DNS_LOCALSTATEDIR=\"/var\"
CPPFLAGS+=	-DNS_SYSCONFDIR=\"/etc/namedb\"

LDADD+=		-L${.CURDIR}/../libdns -ldns
DPADD+=		${.CURDIR}/../libdns/libdns.a

LIBBINDDIR=	${.CURDIR}/../../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

proginstall:

.include <bsd.prog.mk>
