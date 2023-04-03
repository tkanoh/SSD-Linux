#	$ssdlinux: Makefile,v 1.1 2004/07/05 07:23:05 todoroki Exp $

.include <bsd.own.mk>

SRCTOPDIR=	${.CURDIR}/../../..
.ifdef	DESTDIR
BUILDTREEDIR=	${DESTDIR}
KERN_COMPILE_OPTIONS= INSTALL_MOD_PATH=${DESTDIR} ARCH=${ARCH}
.else
BUILDTREEDIR=	/
.endif

_KERNEL_CONFIG=	${.CURDIR}/mini.dot.config-${KERNEL_VERSION}.i386

.if ${IPV6} == "yes"
KERNEL_CONFIG=  ${_KERNEL_CONFIG}.ipv6
.else
KERNEL_CONFIG=  ${_KERNEL_CONFIG}
.endif

.MAIN: all
all: build_kernel

build_kernel:
	cp ${KERNEL_CONFIG} ${SRCTOPDIR}/linux/.config
	cd ${SRCTOPDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} oldconfig
	cd ${SRCTOPDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} clean
	cd ${SRCTOPDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} dep
	cd ${SRCTOPDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} bzImage
	cd ${SRCTOPDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} modules

clean:

distclean: clean

menuconfig:
	cp ${KERNEL_CONFIG} ${SRCTOPDIR}/linux/.config
	cd ${SRCTOPDIR}/linux && ${GMAKE} ${KERN_COMPILE_OPTIONS} menuconfig
	cp ${SRCTOPDIR}/linux/.config ${KERNEL_CONFIG}
