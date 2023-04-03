#	$ssdlinux: Makefile,v 1.5 2004/06/25 08:48:19 yamagata Exp $
.include <bsd.own.mk>
.include "${.CURDIR}/../Makefile.inc"

BOOT_FS=	boot-big.fs
BOOT_FS_SIZE=	2880

.ifdef TFTPDEBUG
DEFALT_INDEX=	2
.else
DEFALT_INDEX=	0
.endif

.MAIN: all
all: ${BOOT_FS}	

${BOOT_FS}: menu.lst ${BZIMAGEDIR}/${BZIMAGE} ${INITRDDIR}/${INITRD_FS_GZ}
	rm -f ${DEV_FD}
	mknod --mode=660 ${DEV_FD} b 7 0
	dd if=${DEV_ZERO} of=${BOOT_FS} bs=1k count=${BOOT_FS_SIZE}
	losetup ${DEV_FD} ${BOOT_FS}
	mke2fs -b 1024 -m 0 ${DEV_FD} ${BOOT_FS_SIZE}
	mount -t ext2 ${DEV_FD} ${MOUNT_POINT}
	rm -rf ${MOUNT_POINT}/lost+found
	mv -f ${GRUBSTAGEDIR}/stage2 ${GRUBSTAGEDIR}/stage2-dist
	install -c -m 644 ${.CURDIR}/../../../usr.sbin/grub/stage2_initrd/stage2 ${GRUBSTAGEDIR}/stage2
	grub-install --root-directory=${MOUNT_POINT} '(fd0)'
	mv -f ${GRUBSTAGEDIR}/stage2-dist ${GRUBSTAGEDIR}/stage2
	rm -f ${GRUBDIR}/fat_stage1_5
	rm -f ${GRUBDIR}/ffs_stage1_5
	rm -f ${GRUBDIR}/iso9660_stage1_5
	rm -f ${GRUBDIR}/jfs_stage1_5
	rm -f ${GRUBDIR}/minix_stage1_5
	rm -f ${GRUBDIR}/reiserfs_stage1_5
	rm -f ${GRUBDIR}/ufs2_stage1_5
	rm -f ${GRUBDIR}/vstafs_stage1_5
	rm -f ${GRUBDIR}/xfs_stage1_5
	#must be set RAM disk support and initrd support on 'make menuconfig'
	cp ${BZIMAGEDIR}/${BZIMAGE} ${MOUNT_POINT}/${BZIMAGE}
	cp ${INITRDDIR}/${INITRD_FS_GZ} ${MOUNT_POINT}
	cp menu.lst ${MOUNT_POINT}/boot/grub
	umount ${MOUNT_POINT}
	losetup -d ${DEV_FD}
	cp ${BOOT_FS} tmp.fs
	rm -f ${BOOT_FS}.gz
	gzip -9 ${BOOT_FS}
	mv tmp.fs ${BOOT_FS}
	rm -f ${DEV_FD}
	mknod --mode=660 ${DEV_FD} b 2 0
	chmod 660 ${DEV_FD}

menu.lst:
	sed	-e 's|@DEFALT_INDEX@|${DEFALT_INDEX}|' \
		-e 's|@SSDRELEASENAME@|${SSDRELEASENAME}|g' \
		-e 's|@KERNEL_VERSION@|${KERNEL_VERSION}|g' \
		-e 's|@INITRD_FS_GZ@|${INITRD_FS_GZ}|g' \
		-e 's|@BZIMAGE@|${BZIMAGE}|g' \
		-e 's|@TFTPBOOTDIR@|${TFTPBOOTDIR}|g' \
		-e 's|@TFTPSERVER@|${TFTPSERVER}|g' \
		-e 's|@TARGETHOST@|${TARGETHOST}|g' \
		-e 's|@NETMASK@|${NETMASK}|g' \
		-e 's|@GATEWAY@|${GATEWAY}|g' \
			${MENU_LIST_IN} > menu.lst

clean:
	rm -f ${BOOT_FS} ${BOOT_FS}.gz menu.lst

init:
	umount ${MOUNT_POINT}
	losetup -d ${DEV_LOOP}

install:
