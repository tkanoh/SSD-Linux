#	$ssdlinux: Makefile,v 1.22 2004/12/21 08:02:57 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	man-pages-
DISTVERSION=	2.01
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	ftp://ftp.kernel.org/pub/linux/docs/manpages
DEPENDENT=	share/man
DEPENDENT+=	distrib/i386/distlst/mtree.conf.in.in
DEPENDENT+=	distrib/powerpc-obs2xx/distlst/mtree.conf.in.in
DEPENDENT+=	distrib/powerpc-obs50/distlst/mtree.conf.in.in

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
