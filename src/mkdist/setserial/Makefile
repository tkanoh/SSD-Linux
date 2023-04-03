#	$ssdlinux: Makefile,v 1.3 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	setserial-
DISTVERSION=	2.17
MASTER_SITES=	ftp://tsx-11.mit.edu/pub/linux/sources/sbin
DEPENDENT=	sbin/setserial
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
