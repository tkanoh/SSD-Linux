#	$ssdlinux: Makefile,v 1.8 2004/12/15 08:35:27 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	thttpd-
DISTVERSION=	2.25b
MASTER_SITES=	http://www.acme.com/software/thttpd
DEPENDENT=	contrib/thttpd
DEPENDENT+=	contrib/setup/etc/setup_thttpd.conf.in
DEPENDENT+=	contrib/setup/etc/thttpd.conf
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/httpd
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/httpd

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
