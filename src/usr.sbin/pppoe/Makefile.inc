#	$ssdlinux: Makefile.inc,v 1.6 2004/03/01 09:24:03 yamagata Exp $

BINDIR?=	/usr/sbin
WARNS?=		0
NONLS=		yes

DIST=		${.CURDIR}/../../../dist/rp-pppoe
.PATH:		${DIST}/src ${DIST}/man ${DIST}/configs

CPPFLAGS+=	-Wall -Wstrict-prototypes -ansi -pedantic
CPPFLAGS+=	'-DPPPOE_PATH="/usr/sbin/pppoe"'
CPPFLAGS+=	'-DPPPD_PATH="/usr/sbin/pppd"'
CPPFLAGS+=	'-DPLUGIN_PATH="/usr/libexec/ppp/rp-pppoe.so"'
CPPFLAGS+=	'-DPPPOE_SERVER_OPTIONS="/etc/ppp/pppoe-server-options"'
CPPFLAGS+=	'-DVERSION="3.5"'
CPPFLAGS+=	'-DRP_VERSION="3.5"'
CPPFLAGS+=	-I${.CURDIR}/../include -I${DIST}/src/libevent
