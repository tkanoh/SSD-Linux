#	$ssdlinux: Makefile,v 1.6 2004/06/15 03:39:50 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	pidentd-
DISTVERSION=	3.0.18
MASTER_SITES=	ftp://ftp.lysator.liu.se/pub/ident/servers
LOCAL_PATCHFILES=	main_c.patch
DISTRELEASE=    1
DEPENDENT=	libexec/identd

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
