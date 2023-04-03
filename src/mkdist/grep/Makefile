#	$ssdlinux: Makefile,v 1.8 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	grep-
DISTVERSION=	2.5.1a
EXTRACT_SUFX=	tar.bz2
GNU_DIST=	yes
DEPENDENT=	usr.bin/grep
DEPENDENT+=	distrib/utils/x_grep
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
