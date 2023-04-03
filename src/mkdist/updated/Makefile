#	$ssdlinux: Makefile,v 1.3 2004/12/15 08:35:27 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	updated-
DISTVERSION=	2.11
MASTER_SITES=	ftp://sunsite.sut.ac.jp/pub/archives/linux/sunsite-unc/system/daemons
DEPENDENT=	sbin/update
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
