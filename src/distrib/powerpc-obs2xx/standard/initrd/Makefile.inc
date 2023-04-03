#	$ssdlinux: Makefile.inc,v 1.2 2005/01/06 06:29:05 todoroki Exp $

PCMCIA_NET?=	no
PCMCIA_WLAN?=	no
PCMCIA_IDE?=	no
PCMCIA_SERIAL?=	yes
PCMCIA_USB?=	no
USB_IDE?=	no
USB_IMAGE?=	no
USB_NET?=	no
USB_SERIAL?=	no
USB_WLAN?=	no

LIST_S?= common flashcfg sh dhcpd ifconfig modules named ppp pppoe sendmail vtund
MTREE_CONF_S?= ${LIST_S}

.if ${IPV6} == "yes"
LIST_S+=	ipv6
MTREE_CONF_S+=	ipv6
.endif

.if ${USE_PCMCIA} == "kernel"
LIST_S+=	hotplug pcmcia.base
MTREE_CONF_S+=	hotplug pcmcia.base
.if ${PCMCIA_NET} == "yes"
LIST_S+=	pcmcia.net
.endif
.if ${PCMCIA_WLAN} == "yes"
LIST_S+=	pcmcia.wlan
.if exists(/usr/src/lib/firmware/prism54/isl3890)
LIST_S+=	pcmcia.prism54
.endif
.endif
.if ${PCMCIA_SERIAL} == "yes"
LIST_S+=	pcmcia.serial
.endif
.if ${PCMCIA_IDE} == "yes"
LIST_S+=	pcmcia.ide
.endif
.if ${PCMCIA_USB} == "yes"
LIST_S+=	usb.base
.if ${USB_NET} == "yes"
LIST_S+=	usb.net
.endif
.if ${USB_WLAN} == "yes"
LIST_S+=	usb.wlan
.endif
.if ${USB_SERIAL} == "yes"
LIST_S+=	usb.serial
.endif
.if ${USB_IDE} == "yes"
LIST_S+=	usb.ide
.endif
.if ${USB_IMAGE} == "yes"
LIST_S+=	usb.image
.endif
.endif
.elif ${USE_PCMCIA} != "no"
LIST_S+=	pcmcia-cs.base
MTREE_CONF_S+=	pcmcia-cs.base
.if ${PCMCIA_NET} == "yes"
LIST_S+=	pcmcia-cs.net
.endif
.if ${PCMCIA_WLAN} == "yes"
LIST_S+=	pcmcia-cs.wlan
.endif
.if ${PCMCIA_SERIAL} == "yes"
LIST_S+=	pcmcia-cs.serial
.endif
.if ${PCMCIA_IDE} == "yes"
LIST_S+=	pcmcia-cs.ide
.endif
.endif

FLASHCFG_S?= ${LIST_S}

.include "${.CURDIR}/../../Makefile.inc"

DEV_LOOP=	/dev/loop0
DEV_ZERO=	/dev/zero
MOUNT_POINT=	/mnt
TMPDIR=		/tmp
MODULESDIR=	${DESTDIR}/lib/modules/${KERNEL_VERSION}
UTILSDIR=	${.CURDIR}/../../../utils
COMMON_INITRDDIR=	${.CURDIR}/../../standard/initrd
COMMON_ETCDIR=	${COMMON_INITRDDIR}/etc
INITRD_FS_SIZE?= 24576


MTREE_CONF=	mtree.conf
RAMDISKBINDIR=	${.CURDIR}/../ramdiskbin
LIST=		list
FLASHCFG=	flashcfg
.if defined(CROSS_BUILD)
STRIPBIN=${TARGET_MACHTYPE}-strip
.else
STRIPBIN=strip
.endif

.MAIN: all
all: prebuild ${INITRD_FS_GZ}

prebuild:
.if defined(CONTRIBS)
	for i in ${CONTRIBS}; \
	do \
		if [ ! -f ${SRCTOPDIR}/contrib/$${i}/${BUILD_VERSION_FILE} ]; then \
			(cd ${SRCTOPDIR}/contrib/$${i} && bmake); \
		fi;\
		if [ ! -d /usr/contrib/$${i} ]; then \
			(cd ${SRCTOPDIR}/contrib/$${i} && bmake install); \
		fi;\
	 done
.if defined(CONTRIBS_INSTALL)
	for i in ${CONTRIBS_INSTALL}; \
	do \
		(cd ${SRCTOPDIR}/contrib/$${i} && bmake install); \
	done
.endif
.endif
.if defined(REQUIREMENT)
	${REQUIREMENT}
.endif

${INITRD_FS_GZ}: ${MTREE_CONF} ${LIST} ${FLASHCFG}
	dd if=${DEV_ZERO} of=${.CURDIR}/${INITRD_FS} bs=1k count=${INITRD_FS_SIZE}
	losetup ${DEV_LOOP} ${.CURDIR}/${INITRD_FS}
	mke2fs ${DEV_LOOP} ${INITRD_FS_SIZE}
	mount -t ext2 ${DEV_LOOP} ${MOUNT_POINT}
	dirs=`cat ${.CURDIR}/${MTREE_CONF}`;(cd ${MOUNT_POINT}; \
	for i in $$dirs; do \
		mkdir -p $$i; \
	done )
	CURDIR=${.CURDIR} OBJDIR=${RAMDISKBINDIR} \
		COMMON_ETCDIR=${COMMON_ETCDIR} TARGDIR=${MOUNT_POINT} \
		STRIPBIN=${STRIPBIN} TMPDIR=${TMPDIR} \
		sh ${COMMON_INITRDDIR}/runlist.sh ${.CURDIR}/${LIST}
.if defined(BUILD_CFIMAGE)
	rm -f ${.CURDIR}/${INITRD_FS_GZ}
	(cd ${MOUNT_POINT} && tar czvpf ${.CURDIR}/${INITRD_FS_GZ} .)
	umount ${MOUNT_POINT}
	losetup -d ${DEV_LOOP}
	rm -f ${.CURDIR}/${INITRD_FS}
.else
	umount ${MOUNT_POINT}
	losetup -d ${DEV_LOOP}
	rm -f ${.CURDIR}/${INITRD_FS_GZ}
	gzip -9 ${.CURDIR}/${INITRD_FS}
.endif

clean: init
	rm -f 	${INITRD_FS_GZ} ${INITRD_FS} \
		${MTREE_CONF} ${MTREE_CONF}.tmp \
		${LIST} ${LIST}.tmp ${FLASHCFG}

init:
	-umount ${MOUNT_POINT}
	-losetup -d ${DEV_LOOP}

${MTREE_CONF} ${LIST}: ${.TARGET}.tmp 
	sed -e 's|@KERNEL_VERSION@|${KERNEL_VERSION}|' \
	    -e 's|@SRCTOPDIR@|${SRCTOPDIR}|' \
	    -e 's|@UTILSDIR@|${UTILSDIR}|' \
	    -e 's|@MODULESDIR@|${MODULESDIR}|' \
	    -e 's|@COMMON_ETCDIR@|${COMMON_ETCDIR}|' \
	    -e 's|@CURDIR@|${.CURDIR}|' \
	    -e 's|@OPENBLOCKS@|${TARGET_OPENBLOCKS}|' \
	    -e '/^#/d' ${.TARGET}.tmp > ${.TARGET}

${MTREE_CONF}.tmp:
	rm -f ${.TARGET}
	for i in ${MTREE_CONF_S}; \
	do \
		if [ -f ${COMMON_INITRDDIR}/${MTREE_CONF}_in/$${i} ]; then \
			sed -e '/^#/d' ${COMMON_INITRDDIR}/${MTREE_CONF}_in/$${i} >> ${.TARGET}; \
		fi; \
	done; \
	if [ -f ${MTREE_CONF}.in ]; then \
		sed -e '/^#/d' ${MTREE_CONF}.in >> ${.TARGET}; \
	fi

${LIST}.tmp:
	rm -f ${.TARGET}
	for i in ${LIST_S}; \
	do \
		if [ -f ${COMMON_INITRDDIR}/${LIST}_in/$${i} ]; then \
			sed -e '/^#/d' ${COMMON_INITRDDIR}/${LIST}_in/$${i} >> ${.TARGET}; \
		fi; \
	done; \
	if [ -f ${LIST}.in ]; then \
		sed -e '/^#/d' ${LIST}.in >> ${.TARGET}; \
	fi

${FLASHCFG}:
	rm -f ${.TARGET}
	for i in ${FLASHCFG_S}; \
	do \
		if [ -f ${COMMON_INITRDDIR}/${FLASHCFG}_in/$${i} ]; then \
			sed -e '/^#/d' ${COMMON_INITRDDIR}/${FLASHCFG}_in/$${i} >> ${.TARGET}; \
		fi; \
	done; \
	if [ -f ${FLASHCFG}.in ]; then \
		sed -e '/^#/d' ${FLASHCFG}.in >> ${.TARGET}; \
	fi

install:
