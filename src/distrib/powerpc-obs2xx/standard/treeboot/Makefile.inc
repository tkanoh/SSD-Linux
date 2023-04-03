#	$ssdlinux: Makefile.inc,v 1.1 2004/12/02 01:54:34 todoroki Exp $

.include "${.CURDIR}/../../Makefile.inc"

KERNSRCDIR=	${SRCTOPDIR}/linux
TRIMAGEDIR=	${KERNSRCDIR}/arch/ppc/boot/images
TRBOOTIMG=	zImage.initrd.treeboot${EXTENSION}

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
	mv ${TRIMAGEDIR}/zImage.initrd.treeboot ${TRBOOTIMG}

clean:
	rm -f ${TRBOOTIMG}

menuconfig:
	(cd ${KERNSRCDIR} && ${GMAKE} ${.TARGET})

oldconfig:
	(cd ${KERNSRCDIR} && ${GMAKE} ${.TARGET})

dep:
	(cd ${KERNSRCDIR} && ${GMAKE} ${.TARGET})

update:
.if !defined(CROSS_BUILD)
.if ${OPENBLOCKS} == "obs200"
	flashcfg f ${TRBOOTIMG} check
.else
	flashcfg -f ${TRBOOTIMG}
.endif
.endif

bootp:
	cp ${TRBOOTIMG} /tftpboot/${TRBOOTIMG}

install:
