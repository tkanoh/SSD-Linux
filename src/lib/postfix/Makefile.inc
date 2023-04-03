#	$ssdlinux: Makefile.inc,v 1.4 2002/12/29 04:00:40 kanoh Exp $

BINDIR?=	/usr/lib
WARNS?=		0
NONLS=		yes

CPPFLAGS+=	-Wmissing-prototypes -Wformat -DLINUX2

CPPFLAGS+=	-I${DIST}/src/util
CPPFLAGS+=	-I${DIST}/src/global
CPPFLAGS+=	-I${DIST}/src/dns
CPPFLAGS+=	-I${DIST}/src/master
.if defined(CROSS_BUILD)
CPPFLAGS+=	-I${DIST}/../../lib/libdb
.endif
