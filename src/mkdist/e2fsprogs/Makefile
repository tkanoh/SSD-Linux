#	$ssdlinux: Makefile,v 1.18 2005/03/02 06:14:34 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	e2fsprogs-
DISTVERSION=	1.36
MASTER_SITES=	ftp://download.sourceforge.net/pub/sourceforge/e2fsprogs
.if ${TARGET_HOSTTYPE} == "powerpc"
LOCAL_PATCHFILES=	${DISTNAME}${DISTVERSION}-unix_c.patch
DISTRELEASE=	1
.endif
# lib
DEPENDENT=	lib/e2fsprogs
# e2fsck
DEPENDENT+=	sbin/e2fsck
# debugfs
DEPENDENT+=	sbin/debugfs
# misc
DEPENDENT+=	sbin/mke2fs usr.sbin/badblocks sbin/tune2fs sbin/dumpe2fs 
DEPENDENT+=	sbin/blkid sbin/logsave sbin/filefrag
DEPENDENT+=	sbin/e2image sbin/fsck
DEPENDENT+=	sbin/chattr sbin/lsattr sbin/uuidgen sbin/mklost+found
DEPENDENT+=	lib/e2fsprogs/e2initrd_helper
# resize
DEPENDENT+=	sbin/resize2fs
#
DEPENDENT+=	distrib/i386/ramdiskbin/ramdiskbin.conf.in
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs50/initrd/list_in/common
DEPENDENT+=	distrib/i386/distlist/mtree.conf.in.in
DEPENDENT+=	distrib/powerpc-obs2xx/distlst
DEPENDENT+=	distrib/powerpc-obs50/distlst

# See also dump which uses e2fsprogs
DEPENDENT+=	lib/dump sbin/dump sbin/restore
DEPENDENT+=	distrib/utils/x_dump

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
