#	$ssdlinux: Makefile,v 1.9 2005/03/18 02:26:54 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	findutils-
DISTVERSION=	4.2.20
GNU_DIST=	yes
# gnulib/lib, lib
DEPENDENT=	lib/findutils
# locate
DEPENDENT+=	libexec/frcode libexec/code libexec/bigram
# find
DEPENDENT+=	usr.bin/find
# xargs
DEPENDENT+=	usr.bin/xargs
# locate
DEPENDENT+=	usr.bin/locate
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
