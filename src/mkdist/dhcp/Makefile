#	$ssdlinux: Makefile,v 1.13 2005/03/02 01:42:59 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	dhcp-
DISTVERSION=	3.0.2
MASTER_SITES=	ftp://ftp.isc.org/isc/dhcp
DEPENDENT=	lib/dhcp sbin/dhclient usr.sbin/dhcpd usr.sbin/dhcrelay
DEPENDENT+=	usr.sbin/omshell usr.sbin/dhcp-cltest usr.sbin/dhcp-svtest
DEPENDENT+=	distrib/utils/x_dhclient
DEPENDENT+=	etc/common/dhclient.conf.sample etc/common/dhcpd.conf.sample
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/dhcpd

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
