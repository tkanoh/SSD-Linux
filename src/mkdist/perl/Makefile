#	$ssdlinux: Makefile,v 1.12 2005/01/03 15:24:28 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	perl-
DISTVERSION=	5.8.6
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	ftp://ftp.kddlabs.co.jp/CPAN/src
DEPENDENT=	usr.bin/perl
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/perl
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/perl

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
