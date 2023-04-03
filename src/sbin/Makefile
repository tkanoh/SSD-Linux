#	$ssdlinux: Makefile,v 1.13 2004/08/25 07:06:04 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR= dhclient iptables update loadkeys setserial
SUBDIR+= routed ripquery
SUBDIR+= init halt shutdown killall5 runlevel utmpdump
SUBDIR+= mkfs mkswap blockdev elvtune fsck.minix mkfs.minix mkfs.bfs \
        fsck.cramfs mkfs.cramfs
SUBDIR+= agetty mount umount swapon losetup pivot_root
SUBDIR+= cfdisk fdisk sfdisk hwclock
SUBDIR+= dmesg ctrlaltdel
SUBDIR+= e2fsck debugfs mke2fs tune2fs dumpe2fs blkid logsave filefrag \
         e2image fsck chattr lsattr uuidgen mklost+found \
         resize2fs
SUBDIR+= dump restore insmod modinfo genksyms depmod
SUBDIR+= ifconfig iptunnel
SUBDIR+= ipmaddr mii-tool nameif plipconfig route slattach
SUBDIR+= cardmgr cardctl iwconfig lilo ping mknod sulogin
SUBDIR+= iwconfig ping6 rtsol ip hotplug
.else

SUBDIR= dhclient iptables update loadkeys setserial

# usagi-tool/src/netkit-routed
SUBDIR+= routed ripquery

# sysvinit
SUBDIR+= init halt shutdown killall5 runlevel utmpdump

# util-linux
#   disk-utils
SUBDIR+= mkfs mkswap blockdev elvtune fsck.minix mkfs.minix mkfs.bfs \
	fsck.cramfs mkfs.cramfs
#   login-utils
SUBDIR+= agetty
#   mount
SUBDIR+= mount umount swapon losetup pivot_root
#   fdisk
SUBDIR+= cfdisk fdisk sfdisk 
#   hwclock
SUBDIR+= hwclock
#   sys-utils
SUBDIR+= dmesg ctrlaltdel 

# e2fsprogs
SUBDIR+= e2fsck debugfs mke2fs tune2fs dumpe2fs blkid logsave filefrag \
	 e2image fsck chattr lsattr uuidgen mklost+found \
	 resize2fs

# dump
SUBDIR+= dump restore

# modutils
SUBDIR+= insmod modinfo genksyms depmod

# usagi-tool/src/net-tools
SUBDIR+= ifconfig iptunnel
SUBDIR+= ipmaddr mii-tool nameif plipconfig route slattach

.if ${USE_PCMCIA} != "no"
# pcmcia-cs
SUBDIR+= cardmgr cardctl
.endif

# wireless_tools
SUBDIR+= iwconfig

SUBDIR+= lilo

# usagi-tool/src/netkit-base
SUBDIR+= ping

# coreutils(fileutils)
SUBDIR+= mknod

# shadow 
SUBDIR+= sulogin

# wireless_tools
SUBDIR+= iwconfig

.if ${IPV6} == "yes"
# usagi-tool/src/iputils
SUBDIR+= ping6
# usagi-tool/usagi/rtsol
SUBDIR+= rtsol
.endif
# usagi-tool/src/iproute2
SUBDIR+= ip

# 2.4.26 hotplug
.if ${KERNEL_VERSION} != "2.4.20"
SUBDIR+=        hotplug
.endif

.endif

.include <bsd.subdir.mk>
