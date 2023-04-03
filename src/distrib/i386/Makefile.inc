#	$ssdlinux: Makefile.inc,v 1.3 2004/06/18 08:20:21 yamagata Exp $
DEV_FD=		/dev/fd0
DEV_LOOP=	/dev/loop0
DEV_ZERO=	/dev/zero
MOUNT_POINT=	/mnt
GRUBDIR=	${MOUNT_POINT}/boot/grub
GRUBSTAGEDIR=	/usr/mdec/grub/i386-ssd
BZIMAGE=	bzImage
BZIMAGEDIR=	${.CURDIR}/../../../linux/arch/i386/boot
INITRDDIR=	${.CURDIR}/../initrd
INITRD_FS=	initrd.fs
INITRD_FS_GZ=	${INITRD_FS}.gz
INITRD_FS_SIZE=	4096

MENU_LIST_IN=	${INITRDDIR}/menu.lst.in

TFTPBOOTDIR=	/tftpboot
TFTPSERVER!=	ifconfig eth0 | grep "inet addr:" | sed -e 's/inet addr://' | awk '{print $$1}'
TARGETHOST=	192.168.1.35
NETMASK=	255.255.255.0
GATEWAY=	192.168.1.1

USE_TFTPSERVER=	yes
TFTPDEBUG=	yes
