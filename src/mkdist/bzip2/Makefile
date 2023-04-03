#	$ssdlinux: Makefile,v 1.5 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	bzip2-
DISTVERSION=	1.0.2
MASTER_SITES=	ftp://sourceware.cygnus.com/pub/bzip2/v102
DEPENDENT=	lib/libbz2 usr.bin/bzip2 usr.bin/bzip2recover
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
