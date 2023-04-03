#	$ssdlinux: Makefile,v 1.7 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	ppp-
DISTVERSION=	2.4.3
MASTER_SITES=	ftp://ftp.samba.org/pub/ppp
DEPENDENT=	usr.sbin/ppp
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/ppp
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/ppp

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
