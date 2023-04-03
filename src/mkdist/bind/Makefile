#	$ssdlinux: Makefile,v 1.10 2005/03/14 03:48:29 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	bind-
DISTVERSION=	9.2.5
MASTER_SITES=	ftp://ftp.isc.org/isc/bind9/${DISTVERSION}
DEPENDENT=	lib/bind usr.sbin/bind usr.bin/bind
DEPENDENT+=	distrib/utils/x_bind
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/named
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/named
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
