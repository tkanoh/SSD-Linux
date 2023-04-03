#	$ssdlinux: Makefile,v 1.6 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	sysvinit-
DISTVERSION=	2.85
MASTER_SITES=	ftp://ftp.cistron.nl/pub/people/miquels/sysvinit
DEPENDENT=	sbin/init sbin/halt sbin/shutdown sbin/killall5 sbin/runlevel
DEPENDENT+=	sbin/utmpdump
DEPENDENT+=	usr.bin/last usr.bin/mesg usr.bin/wall
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
