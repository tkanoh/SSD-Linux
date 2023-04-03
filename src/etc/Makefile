#	$ssdlinux: Makefile,v 1.5 2004/08/10 06:56:30 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR=         common pcmcia i386 powerpc-obs2xx powerpc-obs50
SUBDIR+=        dev.i386 dev.powerpc-obs2xx dev.powerpc-obs50
.else

SUBDIR=		common
SUBDIR+=	${TARGET_SSDHOSTTYPEX}
SUBDIR+=	dev.${TARGET_SSDHOSTTYPEX}

.if ${USE_PCMCIA} != "no"
SUBDIR+=	pcmcia
.endif

.endif

.include <bsd.subdir.mk>
