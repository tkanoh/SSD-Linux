#	$ssdlinux: Makefile,v 1.6 2005/02/21 02:58:19 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	zlib-
DISTVERSION=	1.2.2
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	http://www.gzip.org/zlib
DEPENDENT=	lib/libz
DEPENDENT+=	distrib/utils/x_gzip
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
