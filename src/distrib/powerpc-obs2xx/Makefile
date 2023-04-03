#	$ssdlinux: Makefile,v 1.11 2004/12/15 09:32:19 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR=  distlst
SUBDIR+= standard
SUBDIR+= product
SUBDIR+= custom0
SUBDIR+= custom1
SUBDIR+= custom2
SUBDIR+= standard-big
SUBDIR+= product-big
SUBDIR+= standard-pcmcia
SUBDIR+= product-pcmcia
SUBDIR+= cfroot
.else
SUBDIR=  distlst
SUBDIR+= standard
SUBDIR+= product
.if ${TARGET_SSDHOSTTYPE} == "powerpc-obs266"
SUBDIR+= standard-big
SUBDIR+= product-big
SUBDIR+= standard-pcmcia
SUBDIR+= product-pcmcia
.endif
SUBDIR+= cfroot
.endif

.include <bsd.subdir.mk>
