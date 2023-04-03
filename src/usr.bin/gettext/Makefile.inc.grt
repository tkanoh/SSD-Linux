#	$ssdlinux: Makefile.inc.grt,v 1.1 2003/06/03 05:17:08 yamagata Exp $

.include <bsd.own.mk>

.include "${.CURDIR}/../Makefile.inc"

CPPFLAGS+=	-DHAVE_CONFIG_H
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DHAVE_ARGZ_H="1"
CPPFLAGS+=	-DHAVE_SYS_PARAM_H="1"
CPPFLAGS+=	-DINTDIV0_RAISES_SIGFPE="1"
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DINTDIV0_RAISES_SIGFPE="0"
.endif
