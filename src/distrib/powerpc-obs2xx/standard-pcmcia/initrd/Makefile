#	$ssdlinux: Makefile,v 1.1 2004/12/14 04:25:59 todoroki Exp $

.include <bsd.own.mk>
.include "../Makefile.inc"

PCMCIA_NET=	yes
PCMCIA_WLAN=	yes
PCMCIA_IDE=	yes
PCMCIA_SERIAL=	yes

LIST_S= common flashcfg bash dhcpd ifconfig modules named ppp pppoe \
	sendmail vtund
INITRD_FS_SIZE= 32768

.include "${.CURDIR}/../../standard/initrd/Makefile.inc"

