#	$ssdlinux: Makefile,v 1.9 2004/12/22 08:45:00 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	tar-
DISTVERSION=	1.15.1
EXTRACT_SUFX=	tar.bz2
GNU_DIST=	yes
LOCAL_PATCHFILES=	tar-1.15.1.flashcfg.diff
DEPENDENT=	usr.bin/tar
DEPENDENT+=	distrib/utils/x_tar
DEPENDENT+=	distrib/i386/ramdiskbin/ramdiskbin.conf.in
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs50/standard/initrd/list_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
