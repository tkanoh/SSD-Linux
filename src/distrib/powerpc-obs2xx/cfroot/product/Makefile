#	$ssdlinux: Makefile,v 1.3 2004/12/22 04:15:32 todoroki Exp $

.include <bsd.own.mk>

PCMCIA_NET=	yes
PCMCIA_WLAN=	yes
PCMCIA_IDE=	yes
PCMCIA_SERIAL=	yes

EXTENSION=	-product
LIST_S= common bash cfbin dhcpd modules named ppp pppoe \
	sendmail sshd ssh vtund useradd httpd setup_cgi
INITRD_FS_SIZE= 32768
BUILD_CFIMAGE=yes

.include "${.CURDIR}/../../standard/initrd/Makefile.inc"
