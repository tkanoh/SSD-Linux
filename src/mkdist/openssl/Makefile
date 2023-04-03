#	$ssdlinux: Makefile,v 1.16 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	openssl-
DISTVERSION=	0.9.7e
MASTER_SITES=	http://www.openssl.org/source
DEPENDENT=	lib/ssl
DEPENDENT+=	usr.bin/openssl
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/sshd
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/sshd

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
