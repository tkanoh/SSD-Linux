#	$ssdlinux: Makefile,v 1.7 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	ed-
DISTVERSION=	0.2
GNU_DIST=	yes
LOCAL_PATCHFILES=	buf_c.patch
DISTRELEASE=	1
DEPENDENT=	bin/ed
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
