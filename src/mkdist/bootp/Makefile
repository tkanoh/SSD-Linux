#	$ssdlinux: Makefile,v 1.2 2002/05/24 06:43:09 kanoh Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	bootp-
DISTVERSION=	DD2.4.3
MASTER_SITES=	ftp://sunsite.sut.ac.jp/pub/archives/linux/slackware/source/n/bootp
PATCH_SITES=	${MASTER_SITES}
PATCHFILES=	bootp-DD2.4.3.diff.gz
DEPENDENT=	usr.sbin/bootp

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
