#	$ssdlinux: Makefile,v 1.3 2004/12/15 08:35:25 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	hotplug-
DISTVERSION=	2004_03_29
EXTRACT_SUFX=	tar.gz

MASTER_SITE=	http://voxel.dl.sourceforge.net/sourceforge/linux-hotplug

DEPENDENT=	sbin/hotplug
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/hotplug
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia.base
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/usb.base
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/pcmcia.base
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/usb.base

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
