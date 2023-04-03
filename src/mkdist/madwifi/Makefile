#	$ssdlinux: Makefile,v 1.5 2005/02/09 05:40:03 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	madwifi-
DISTVERSION=	20050209

LOCAL_PATCHFILES=	${DISTNAME}${DISTVERSION}-ssd.diff
DEPENDENT=	lib/modules/wireless/madwifi
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/pcmcia.wlan

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
