#	$ssdlinux: Makefile,v 1.4 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	cron
DISTVERSION=	3.0pl1
MASTER_SITES=	ftp://sunsite.sut.ac.jp/pub/archives/linux/sunsite-unc/system/daemons/cron
LOCAL_PATCHFILES=	cron_c.patch
LOCAL_PATCHFILES+=	misc_c.patch
DISTRELEASE=	1
DEPENDENT=	usr.sbin/cron usr.bin/crontab
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
