#	$ssdlinux: Makefile,v 1.7 2004/11/18 04:06:47 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	newsyslog-
DISTVERSION=	1.1
MASTER_SITES=	ftp://ftp.weird.com/pub/local
LOCAL_PATCHFILES= mksigname.sh.diff 
DISTRELEASE=	3
DEPENDENT=	usr.bin/newsyslog
DEPENDENT+=	etc/common/newsyslog.conf

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
