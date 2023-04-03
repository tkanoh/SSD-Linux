#	$ssdlinux: Makefile,v 1.2 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	pciutils-
DISTVERSION=	2.1.11
EXTRACT_SUFX=	tar.bz2

MASTER_SITE=	ftp://ftp.kernel.org/pub/software/utils

PATCH_SITE=	http://www.linuxfromscratch.org/patches/downloads/pciutils
PATCHFILES=	${DISTNAME}${DISTVERSION}-pcimodules-1.patch

DEPENDENT=	usr.sbin/pciutils
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/hotplug

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
