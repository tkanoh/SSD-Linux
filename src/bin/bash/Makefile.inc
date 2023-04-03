#	$ssdlinux: Makefile.inc,v 1.13 2004/11/18 03:29:17 yamagata Exp $

WARNS?=		0
BINDIR?=	/bin
.if ${FULL_SHARED} != "yes"
LDSTATIC?=	-static -s
.endif
NONLS= yes

BASHVERSION=	3.0
BASHPATCHLEVEL=	16
RELSTATUS=	release

DIST=		${.CURDIR}/../../../dist/bash

CPPFLAGS+=	-DPROGRAM='"bash"'
CPPFLAGS+=	-DCONF_HOSTTYPE='"${TARGET_HOSTTYPE}"'
CPPFLAGS+=	-DCONF_OSTYPE='"linux-gnu"'
CPPFLAGS+=	-DCONF_MACHTYPE='"${TARGET_MACHTYPE}"'
CPPFLAGS+=	-DCONF_VENDOR='"ssd"' 
CPPFLAGS+=	-DLOCALEDIR='"/usr/share/locale"'
CPPFLAGS+=	-DPACKAGE='"bash"'
CPPFLAGS+=	-DSHELL -DHAVE_CONFIG_H
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DHAVE_LONG_DOUBLE=1
CPPFLAGS+=	-DDEV_FD_PREFIX='"/dev/fd/"'
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DWORDS_BIGENDIAN=1
CPPFLAGS+=	-DDEV_FD_PREFIX='"/proc/self/fd/"'
.endif

CPPFLAGS+=	-I${.CURDIR} -I${.CURDIR}/../common 
CPPFLAGS+=	-I${DIST} -I${DIST}/include -I${DIST}/lib
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../termcap
.endif
