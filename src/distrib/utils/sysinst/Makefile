#	$ssdlinux: Makefile,v 1.8 2003/04/19 14:16:38 kanoh Exp $

.include <bsd.own.mk>

PROG=		sysinst
MKMAN=		no

#CPPFLAGS+=	-DDEBUG
CPPFLAGS+=	-DSSDRELEASENAME=\"${SSDRELEASENAME}\"
CPPFLAGS+=	-DDIST_ARCH=\"${TARGET_SSDHOSTTYPE}\"
CPPFLAGS+=	-DKERNEL_VERSION=\"${KERNEL_VERSION}\"
CPPFLAGS+=	-fomit-frame-pointer
.if ${TARGET_HOSTTYPE} == "i386"
GCC_MAJOR_VERSION=	`gcc --version | cut -d . -f 1`
.if ${GCC_MAJOR_VERSION} == "2"
CPUHEAD=	-m
.else
CPUHEAD=	-mcpu=i
.endif
CPPFLAGS+=	${CPUHEAD}386
CPPFLAGS+=	-DPROBE_PCCARD
CPPFLAGS+=	-DINSTALLBOOT
CPPFLAGS+=	-DHAVE_GRUB
CPPFLAGS+=	-DCONF_NETWORK
CPPFLAGS+=	-DHAVE_KERNEL
.endif
.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
CPPFLAGS+=	-DHAVE_CONTRIB
.endif

proginstall:

.include <bsd.prog.mk>
