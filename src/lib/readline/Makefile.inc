#	$ssdlinux: Makefile.inc,v 1.3 2004/08/05 02:39:57 yamagata Exp $

BINDIR=	/usr/lib
INCSDIR= /usr/include/readline
WARNS?=	0
WFORMAT?= 2
NONLS= yes

DIST=		${.CURDIR}/../../../dist/readline
.PATH:		${DIST} ${DIST}/doc

CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-I${.CURDIR}/../ -I${DIST}
CPPFLAGS+=	-DRL_LIBRARY_VERSION=\"5.0\"
