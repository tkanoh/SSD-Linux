#	$ssdlinux: Makefile,v 1.5 2004/12/15 08:35:27 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	termcap-
DISTVERSION=	1.3.1
GNU_DIST=	yes
DEPENDENT=	lib/libtermcap
DEPENDENT+=	cross/powerpc/libtermcap
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
