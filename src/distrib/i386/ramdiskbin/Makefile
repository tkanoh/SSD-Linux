#	$ssdlinux: Makefile,v 1.5 2004/04/16 01:50:06 yamagata Exp $

.MAIN: all
all: ramdiskbin

SRCTOP=		${.CURDIR}/../../..

ramdiskbin: ramdiskbin.conf
	crunchgen -D ${SRCTOP} -f ramdiskbin.conf
	bmake -f ramdiskbin.mk objs exe
	strip ramdiskbin

clean:
	rm -rf agetty badblocks cat basename cardmgr chgrp chmod chown chroot cmp cp date depmod df dhclient dump
	rm -rf e2fsck expr fdisk ftp grep grub gzip
	rm -rf hostname halt ifconfig init insmod login ln ls mkdir mke2fs mknod mkswap mount mv
	rm -rf passwd ping portmap pwd restore rm route 
	rm -rf sed sfdisk sh shutdown sleep sort stty swapon sysinst tar touch umount  uname uniq
	rm -f *.o *.c *.mk *.cro *.cache
	rm -f ramdiskbin ramdiskbin.conf

ramdiskbin.conf: ramdiskbin.conf.in
	rm -f ramdiskbin.conf
	sed -e 's|@SRCTOP@|${SRCTOP}|' ramdiskbin.conf.in > ramdiskbin.conf
	

install:
