#	$ssdlinux: Makefile,v 1.4 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	portmap_
DISTVERSION=	4
MASTER_SITES=	ftp://ftp.porcupine.org/pub/security
DEPENDENT=	usr.sbin/portmap usr.sbin/pmap_dump usr.sbin/pmap_set
DEPENDENT+=	distrib/utils/x_portmap
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
