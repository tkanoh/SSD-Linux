#	$ssdlinux: Makefile.inc,v 1.7 2004/04/28 07:20:04 yamagata Exp $

WARNS?=	0
WFORMAT?= 2
BINDIR?=/usr/bin
NONLS= yes
CPPFLAGS+=      -DHAVE_CONFIG_H
.if ${IPV6} == "yes"
CPPFLAGS+=	-DINET6=1
.endif
.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DHAVE_UNSIGNED_CHAR=1
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
.endif
