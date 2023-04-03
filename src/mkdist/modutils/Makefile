#	$ssdlinux: Makefile,v 1.13 2004/12/15 08:35:25 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	modutils-
DISTVERSION=	2.4.27
EXTRACT_SUFX=	tar.bz2
KERN_DISTDIR=	/utils/kernel/modutils/v${KERNEL_MAJOR}.${KERNEL_MINOR}
# util and obj
DEPENDENT=	lib/modutils
# insmod
DEPENDENT+=	sbin/insmod sbin/modinfo
# genksyms
DEPENDENT+=	sbin/genksyms
# depmod 
DEPENDENT+=	sbin/depmod

DEPENDENT+=	distrib/utils/x_insmod
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/modules
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/modules

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
