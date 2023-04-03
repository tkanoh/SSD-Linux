#	$ssdlinux: Makefile,v 1.9 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	samba-
ORG_VERSION=	2.2.11
JA_VERSION=	1.0
DISTVERSION=	${ORG_VERSION}-ja-${JA_VERSION}
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	ftp://openlab.plathome.co.jp/pub/ftp.samba.gr.jp/samba-jp/samba-${ORG_VERSION}-ja
LOCAL_PATCHFILES=	samba-${ORG_VERSION}-ja-${JA_VERSION}.diff
DEPENDENT=	contrib/samba
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/samba
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/samba

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
