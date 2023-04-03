#	$ssdlinux: Makefile,v 1.4 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	gzip-
DISTVERSION=	1.2.4a
GNU_DIST=	yes
LFS_PATCH_DIST=	yes
LOCAL_PATCHFILES=	gzexe_in.patch
DISTRELEASE=	1
DEPENDENT=	usr.bin/gzip
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
