#	$ssdlinux: Makefile,v 1.2 2004/06/25 08:48:19 yamagata Exp $
.include <bsd.own.mk>
.include "${.CURDIR}/../Makefile.inc"

INST_FS=	inst.fs
INST_FS_SIZE=	1440

.MAIN: all
all: ${INST_FS}	

${INST_FS}: ${INITRDDIR}/${INITRD_FS_GZ}
	rm -f ${DEV_FD}
	mknod --mode=660 ${DEV_FD} b 7 0
	dd if=${DEV_ZERO} of=${INST_FS} bs=1k count=${INST_FS_SIZE}
	losetup ${DEV_FD} ${INST_FS}
	mke2fs -b 1024 -m 0 ${DEV_FD} ${INST_FS_SIZE}
	mount -t ext2 ${DEV_FD} ${MOUNT_POINT}
	rm -rf ${MOUNT_POINT}/lost+found
	cp ${INITRDDIR}/${INITRD_FS_GZ} ${MOUNT_POINT}
	umount ${MOUNT_POINT}
	losetup -d ${DEV_FD}
	cp ${INST_FS} tmp.fs
	rm -f ${INST_FS}.gz
	gzip -9 ${INST_FS}
	mv tmp.fs ${INST_FS}
	rm -f ${DEV_FD}
	mknod --mode=660 ${DEV_FD} b 2 0
	chmod 660 ${DEV_FD}

clean:
	rm -f ${INST_FS} ${INST_FS}.gz

init:
	umount ${MOUNT_POINT}
	losetup -d ${DEV_LOOP}

install:
