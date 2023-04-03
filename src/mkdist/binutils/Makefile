#	$ssdlinux: Makefile,v 1.15 2003/02/12 04:56:20 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	binutils-
DISTVERSION=	2.13.90.0.18
EXTRACT_SUFX=	tar.bz2
KERN_DISTDIR=	/devel/binutils
DISTRELEASE=	1
DEPENDENT=	usr.bin/binutils
DEPENDENT+=	cross/powerpc/binutils
DEPENDENT+=	tools/binutils

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
