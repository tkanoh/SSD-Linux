#	$ssdlinux: Makefile,v 1.4 2005/03/11 07:38:56 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	tnftp-
DISTVERSION=	20050103
MASTER_SITES=	ftp://ftp.netbsd.org/pub/NetBSD/misc/tnftp
DEPENDENT=	usr.bin/ftp
DEPENDENT+=	distrib/utils/x_ftp
DEPENDENT+=	distrib/i386/ramdiskbin/ramdiskbin.conf.in
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
