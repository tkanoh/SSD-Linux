#	$ssdlinux: Makefile,v 1.13 2005/02/25 07:23:34 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	ex-
DISTVERSION=	050225
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	http://keihanna.dl.sourceforge.net/sourceforge/ex-vi
DEPENDENT=	libexec/expreserve libexec/exrecover usr.bin/ex
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs50/initrd/list_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
