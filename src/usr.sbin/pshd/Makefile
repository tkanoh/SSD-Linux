#	$ssdlinux: Makefile,v 1.9 2003/12/28 21:11:49 kanoh Exp $

.include <bsd.own.mk>

PROG=	pshd		
MKMAN=	no

.if exists(/usr/include/asm/pushsw_obs2xx.h)
CPPFLAGS+= -DHAVE_PUSHSW_OBS2XX_H
.endif

.ifdef NEW_KERNEL_PATCH
.if ${NEW_KERNEL_PATCH} == "20030328"
NO_UPSCTL= yes
.endif
.endif

.if ${TARGET_SSDHOSTTYPE} == "powerpc-obs266"
.ifndef NO_UPSCTL
CPPFLAGS+= -DCONFIG_OPENBLOCKS266 -DCONFIG_OBS266
.endif
.endif

.include <bsd.prog.mk>
