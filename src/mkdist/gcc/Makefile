#	$ssdlinux: Makefile,v 1.18 2005/03/19 22:21:30 kanoh Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	gcc-
DISTVERSION=	${GCC_VERSION}
MASTER_SITES=	ftp://ftp.iij.ad.jp/pub/gcc/releases/${DISTNAME}${GCC_VERSION}
EXTRACT_SUFX=	tar.bz2

DISTRELEASE=	2

DEPENDENT=	usr.bin/gcc
DEPENDENT+=	cross/powerpc/gcc
DEPENDENT+=	cross/powerpc/gcc-core
DEPENDENT+=	tools/gcc
DEPENDENT+=	tools/gcc-core

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
