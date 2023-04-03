#	$ssdlinux: Makefile,v 1.6 2004/06/15 09:18:36 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	lpr_
DISTVERSION=	2000.05.07
MASTER_SITES=	ftp://ftp.debian.org/debian/pool/main/l/lpr
EXTRACT_SUFX=	orig.tar.gz
PATCH_SITES=	${MASTER_SITES}
PATCHFILES=	${DISTNAME}${DISTVERSION}-5.diff.gz
LOCAL_PATCHFILES=	printjob_c.patch
DISTRELEASE=	4
ALTRENAMEDISTDIR=       mv ${DISTDIR}/lpr-${DISTVERSION}.orig ${DISTDIR}/lpr
DEPENDENT=	usr.sbin/lpr

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
