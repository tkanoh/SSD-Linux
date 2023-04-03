#	$ssdlinux: Makefile,v 1.8 2004/12/27 02:43:48 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	db-
DISTVERSION=	4.3.27
MASTER_SITES=	http://www.sleepycat.com/update/snapshot
DEPENDENT=	lib/libdb
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
