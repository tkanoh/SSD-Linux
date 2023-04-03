#	$ssdlinux: Makefile,v 1.3 2002/12/26 14:28:36 kanoh Exp $

.include <bsd.own.mk>

PROG=		freeramdisk
MKMAN=		no

.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-m386
.endif

.include <bsd.prog.mk>
