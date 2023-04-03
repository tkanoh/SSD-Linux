#	$ssdlinux: Makefile,v 1.10 2005/03/10 07:11:19 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	iptables-
DISTVERSION=	1.3.1
MASTER_SITES=	http://www.netfilter.org/files
EXTRACT_SUFX=	tar.bz2
DEPENDENT=	lib/iptables sbin/iptables
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
