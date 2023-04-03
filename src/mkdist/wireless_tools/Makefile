#	$ssdlinux: Makefile,v 1.10 2004/12/14 08:46:36 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	wireless_tools.
DISTVERSION=	27
MASTER_SITES=	http://www.hpl.hp.com/personal/Jean_Tourrilhes/Linux
DEPENDENT=	lib/libiw
DEPENDENT+=	sbin/iwconfig
DEPENDENT+=	usr.sbin/iwlist usr.sbin/iwpriv usr.sbin/iwspy usr.sbin/iwgetid
DEPENDENT+=	usr.sbin/iwevent usr.sbin/ifrename
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/pcmcia.wlan
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/pcmcia-cs.wlan

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
