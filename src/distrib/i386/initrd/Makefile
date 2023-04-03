#	$ssdlinux: Makefile,v 1.7 2004/08/14 03:14:20 yamagata Exp $

.include <bsd.own.mk>
.include "${.CURDIR}/../Makefile.inc"

MODULESDIR=	${DESTDIR}/lib/modules/${KERNEL_VERSION}

MTREE_CONF=	mtree.conf
RAMDISKBINDIR=	${.CURDIR}/../ramdiskbin
LIST=		list

.MAIN: all
all: ${INITRD_FS_GZ}

${INITRD_FS_GZ}: ${MTREE_CONF} ${LIST} 
	dd if=${DEV_ZERO} of=${.CURDIR}/${INITRD_FS} bs=1k count=${INITRD_FS_SIZE}
	losetup ${DEV_LOOP} ${.CURDIR}/${INITRD_FS}
	mke2fs -m 0 ${DEV_LOOP} ${INITRD_FS_SIZE}
	mount -t ext2 ${DEV_LOOP} ${MOUNT_POINT}
	rm -rf ${MOUNT_POINT}/lost+found
	dirs=`cat ${.CURDIR}/${MTREE_CONF}`;(cd ${MOUNT_POINT}; \
	for i in $$dirs; do \
		mkdir -p $$i; \
	done )
	chmod 1777 ${MOUNT_POINT}/tmp
	rm -f etc/rc
	sed	-e 's|@SSDRELEASENAME@|${SSDRELEASENAME}|g' \
		-e 's|@KERNEL_VERSION@|${KERNEL_VERSION}|g' \
		etc/rc.in > etc/rc
	chmod 555 etc/rc
	CURDIR=${.CURDIR} OBJDIR=${RAMDISKBINDIR} \
		TARGDIR=${MOUNT_POINT} sh ${.CURDIR}/runlist.sh ${.CURDIR}/${LIST}
	umount ${MOUNT_POINT}
	losetup -d ${DEV_LOOP}
	rm -f ${.CURDIR}/${INITRD_FS_GZ}
	gzip -9 ${.CURDIR}/${INITRD_FS}

clean: init
	rm -f ${INITRD_FS_GZ} etc/rc ${MTREE_CONF} ${LIST}

init:
	-umount ${MOUNT_POINT}
	-losetup -d ${DEV_LOOP}

${MTREE_CONF}: ${.TARGET}.in
	sed 	-e 's|@KERNEL_VERSION@|${KERNEL_VERSION}|' \
		-e 's|@MODULESDIR@|${MODULESDIR}|' \
		${.TARGET}.in > ${.TARGET}

${LIST}: ${.TARGET}.in.${USE_PCMCIA}
	sed	-e 's|@KERNEL_VERSION@|${KERNEL_VERSION}|' \
		-e 's|@MODULESDIR@|${MODULESDIR}|' \
		${.TARGET}.in.${USE_PCMCIA} > ${.TARGET}
install:
.ifdef USE_TFTPSERVER
	if [ ! -d ${TFTPBOOTDIR} ] ; then \
		mkdir ${TFTPBOOTDIR}; \
		chmod 777 ${TFTPBOOTDIR}; fi
	cp ${BZIMAGEDIR}/${BZIMAGE} ${TFTPBOOTDIR}
	cp ${INITRD_FS_GZ} ${TFTPBOOTDIR}
	chmod 666 ${TFTPBOOTDIR}/${BZIMAGE}
	chmod 666 ${TFTPBOOTDIR}/${INITRD_FS_GZ}
.endif
