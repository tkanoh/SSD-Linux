#	$ssdlinux: Makefile,v 1.11 2004/08/25 07:06:04 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR= net usb pcmcia wireless
.else

SUBDIR=

.if ${KERNEL_VERSION} != "2.4.20"
.if ${TARGET_SSDHOSTTYPE} != "powerpc-obs50"
SUBDIR+= usb
.endif
.else
.if ${TARGET_SSDHOSTTYPE} == "powerpc-obs200"
SUBDIR+= usb
.endif
.endif

.if ${USE_PCMCIA} == "kernel
SUBDIR+= pcmcia wireless
.elif ${USE_PCMCIA} != "no"
SUBDIR+= net pcmcia
.endif

.endif

.include <bsd.subdir.mk>
