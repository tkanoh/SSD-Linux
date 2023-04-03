#	$ssdlinux: Makefile,v 1.3 2004/12/15 08:35:27 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	tnftpd-
DISTVERSION=	20040810
MASTER_SITES=	ftp://ftp.netbsd.org/pub/NetBSD/misc/tnftp
DEPENDENT=	libexec/ftpd
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
