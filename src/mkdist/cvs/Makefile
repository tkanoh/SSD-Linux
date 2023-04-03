#	$ssdlinux: Makefile,v 1.21 2005/02/10 07:17:31 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	cvs-
DISTVERSION=	1.11.19
MASTER_SITES=	https://ccvs.cvshome.org/files/documents/19/742
EXTRACT_SUFX=	tar.bz2
PATCH_SITES=	ftp://ftp.kame.net/pub/kame/misc
PATCHFILES=	cvs-${DISTVERSION}-v6-20050205.diff.gz
LOCAL_PATCHFILES=	client_c.patch
LOCAL_PATCHFILES+=	rcs_c.patch
DEPENDENT=	usr.bin/cvs

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
