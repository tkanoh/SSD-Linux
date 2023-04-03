#	$ssdlinux: Makefile.inc,v 1.3 2004/12/02 04:19:14 todoroki Exp $
SRCTOPDIR=	${.CURDIR}/../../../..
INITRDDIR=	${.CURDIR}/../initrd
.if defined(BUILD_CFIMAGE)
INITRD_FS=	cfroot.image${EXTENSION}
INITRD_FS_GZ=	${INITRD_FS}.tgz
.else
INITRD_FS=	ramdisk.image${EXTENSION}
INITRD_FS_GZ=	${INITRD_FS}.gz
.endif
