#	$ssdlinux: Makefile,v 1.5 2004/11/24 01:24:38 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	Linux-PAM-
DISTVERSION=	0.77
EXTRACT_SUFX=	tar.bz2
KERNL_ORG_DIR=	/libs/pam/pre/library
#LOCAL_PATCHFILES=	pam_localuser_c.patch
#LOCAL_PATCHFILES+=	pam_xauth_c.patch
DEPENDENT=	lib/pam

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
