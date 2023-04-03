#	$ssdlinux: Makefile.inc,v 1.3 2004/08/24 07:59:29 kanoh Exp $

.include "${.CURDIR}/../Makefile.inc"

KERNSRCDIR=	${SRCTOPDIR}/linux
TRIMAGEDIR=	${KERNSRCDIR}/arch/ppc/boot/images
.if ${KERNEL_VERSION} == "2.4.20"
_TRBOOTIMG=	zImage.initrd.elf
.else
_TRBOOTIMG=	zImage.initrd.embedded
.endif
TRBOOTIMG=	${_TRBOOTIMG}${EXTENSION}

.ifdef	DESTDIR
KERN_COMPILE_OPTIONS= INSTALL_MOD_PATH=${DESTDIR} ARCH=${ARCH}
.endif
.if defined(CROSS_BUILD)
KERN_COMPILE_OPTIONS+= CROSS_COMPILE=${TARGET_MACHTYPE}-
.else
KERN_COMPILE_OPTIONS+=
.endif

.MAIN: all
all: ${TRBOOTIMG}

${TRBOOTIMG}:
	cp ${INITRDDIR}/${INITRD_FS_GZ} ${TRIMAGEDIR}/ramdisk.image.gz
	(cd ${KERNSRCDIR} && ${GMAKE} ${KERN_COMPILE_OPTIONS} zImage.initrd )
	mv ${TRIMAGEDIR}/${_TRBOOTIMG} ${TRBOOTIMG}

clean:
	rm -f ${TRBOOTIMG}

menuconfig:
	(cd ${KERNSRCDIR} && ${GMAKE} ${.TARGET})

oldconfig:
	(cd ${KERNSRCDIR} && ${GMAKE} ${.TARGET})

dep:
	(cd ${KERNSRCDIR} && ${GMAKE} ${.TARGET})

bootp:
	cp ${TRBOOTIMG} /tftpboot/${TRBOOTIMG}

install:
