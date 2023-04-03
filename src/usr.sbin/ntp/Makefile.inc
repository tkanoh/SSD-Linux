#	$ssdlinux: Makefile.inc,v 1.5 2004/10/01 02:44:45 yamagata Exp $

WARNS?=	0
WFORMAT?= 2
BINDIR?=/usr/sbin
NONLS= yes

DIST=		${.CURDIR}/../../../dist/ntp

CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-Wall -Wcast-qual -Wmissing-prototypes -Wpointer-arith
CPPFLAGS+=	-Wshadow -Wstrict-prototypes -pipe
CPPFLAGS+=	-I${.CURDIR}/../ -I${DIST}/include -I${DIST}
CPPFLAGS+=	-DSTR_SYSTEM='"${TARGET_MACHTYPE}"'
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DNO_PARENB_IGNPAR=1
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif
