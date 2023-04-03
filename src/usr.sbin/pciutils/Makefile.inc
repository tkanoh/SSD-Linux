#	$ssdlinux: Makefile.inc,v 1.1 2004/08/09 04:36:06 todoroki Exp $

WARNS?=	0
WFORMAT?= 2
BINDIR?=/usr/sbin
NONLS= yes

DIST=		${.CURDIR}/../../../dist/pciutils

CPPFLAGS+=	-I${.CURDIR}/../libpci -I${DIST}/lib -I${DIST}

LDADD+=		-L${.CURDIR}/../libpci -lpci
DPADD+=		${.CURDIR}/../libpci/libpci.a
