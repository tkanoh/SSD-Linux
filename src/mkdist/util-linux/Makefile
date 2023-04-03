#	$ssdlinux: Makefile,v 1.29 2005/01/27 06:56:33 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	util-linux-
DISTVERSION=	2.12q
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	ftp://ftp.win.tue.nl/pub/linux-local/utils/util-linux/
# lib
DEPENDENT=	lib/util-linux
# getopt
DEPENDENT+=	usr.bin/getopt
# disk-utils
DEPENDENT+=	sbin/mkfs sbin/mkswap sbin/blockdev sbin/elvtune sbin/fsck.minix
DEPENDENT+=	sbin/mkfs.minix sbin/mkfs.bfs sbin/fsck.cramfs sbin/mkfs.cramfs
DEPENDENT+=	usr.bin/fdformat usr.bin/isosize usr.bin/setfdprm usr.bin/raw
# login-utils
DEPENDENT+=	sbin/agetty
# misc-utils
DEPENDENT+=	usr.bin/cal usr.bin/chkdupexe usr.bin/ddate usr.bin/logger
DEPENDENT+=	usr.bin/look usr.bin/mcookie usr.bin/namei usr.bin/rename
DEPENDENT+=	usr.bin/script usr.bin/whereis usr.bin/setterm 
# mount
DEPENDENT+=	sbin/mount sbin/umount sbin/swapon sbin/losetup sbin/pivot_root
# fdisk
DEPENDENT+=	sbin/cfdisk sbin/fdisk sbin/sfdisk
# hwclock
DEPENDENT+=	sbin/hwclock
# sys-utils
DEPENDENT+=	usr.bin/arch sbin/dmesg
DEPENDENT+=	usr.bin/cytune usr.bin/flock usr.bin/ipcrm
DEPENDENT+=	usr.bin/ipcs usr.bin/renice usr.bin/setsid usr.sbin/readprofile
DEPENDENT+=	usr.sbin/tunelp sbin/ctrlaltdel usr.sbin/rdev 
# text-utils
DEPENDENT+=	usr.bin/col usr.bin/colcrt usr.bin/colrm usr.bin/column
DEPENDENT+=	usr.bin/hexdump usr.bin/rev usr.bin/line usr.bin/tailf
DEPENDENT+=	usr.bin/pg usr.bin/more usr.bin/ul

DEPENDENT+=	distrib/utils/x_login_no_shadow
DEPENDENT+=	distrib/utils/x_mount distrib/utils/x_mount_no_nfs
DEPENDENT+=	distrib/utils/x_umount distrib/utils/x_umount_no_nfs
DEPENDENT+=	distrib/i386/ramdiskbin/ramdiskbin.conf.in
DEPENDENT+=	distrib/i386/distlst/mtree.conf.in
DEPENDENT+=	distrib/powerpc-obs2xx/distlst/mtree.conf.in.in
DEPENDENT+=	distrib/powerpc-obs50/distlst/mtree.conf.in.in
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
