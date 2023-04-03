#	$ssdlinux: Makefile,v 1.19 2004/12/15 08:35:26 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	pcmcia-cs-
DISTVERSION=	3.2.8
MASTER_SITES=	ftp://download.sourceforge.net/pub/sourceforge/pcmcia-cs
LOCAL_PATCHFILES= pcmcia-cs-3.2.4.obs2xx.diff
LOCAL_PATCHFILES+= obs2xx_cardbus_patch.diff
LOCAL_PATCHFILES+= tulip_cb-mii-tool.diff
DEPENDENT=	lib/modules sbin/cardmgr sbin/cardctl usr.bin/pcmcia-cs
DEPENDENT+=	etc/pcmcia
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia-cs.base
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia-cs.ide
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia-cs.net
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia-cs.serial
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia-cs.wlan
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia.base
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia.ide
DEPENDENT+=	distrib/poweroc-obs2xx/standard/initrd/list_in/pcmcia.serial

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
