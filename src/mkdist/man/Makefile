#	$ssdlinux: Makefile,v 1.12 2005/01/11 01:37:09 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	man-
DISTVERSION=	1.5p
MASTER_SITES=	ftp://ftp.win.tue.nl/pub/linux-local/utils/man
EXTRACT_SUFX=	tar.bz2
DEPENDENT=	usr.bin/man usr.bin/apropos usr.bin/whatis
DEPENDENT+=	usr.sbin/makewhatis
DEPENDENT+=	etc/common/man.conf

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
