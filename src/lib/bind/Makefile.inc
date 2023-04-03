#	$ssdlinux: Makefile.inc,v 1.8 2005/03/14 03:47:44 yamagata Exp $

WARNS?=	0
WFORMAT?= 2
NONLS= yes

ISCDIST=	${.CURDIR}/../../../dist/bind/lib/isc

CPPFLAGS+=	-W -Wall -Wmissing-prototypes -Wcast-qual -Wwrite-strings
CPPFLAGS+=	-I${.CURDIR}/../include

CPPFLAGS+=	-DVERSION=\"9.2.5\"
