#	$ssdlinux: Makefile,v 1.4 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	diffutils-
DISTVERSION=	2.8.1
GNU_DIST=	yes
DEPENDENT=	usr.bin/cmp usr.bin/diff usr.bin/diff3 usr.bin/sdiff
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
