#	$ssdlinux: Makefile,v 1.18 2005/01/31 03:28:56 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	sed-
DISTVERSION=	4.1.4
GNU_DIST=	yes
DEPENDENT=	usr.bin/sed
DEPENDENT+=	distrib/utils/x_sed
DEPENDENT+=	distrib/i386/ramdiskbin/ramdiskbin.conf.in
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
