#	$ssdlinux: Makefile,v 1.4 2005/02/10 09:04:18 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	usbutils-
DISTVERSION=	0.70

MASTER_SITE=	http://jaist.dl.sourceforge.net/sourceforge/linux-usb

DEPENDENT=	usr.sbin/usbutils
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/usb.base
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/usb.base

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
