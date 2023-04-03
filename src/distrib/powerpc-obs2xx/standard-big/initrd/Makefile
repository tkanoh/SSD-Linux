#	$ssdlinux: Makefile,v 1.3 2004/12/14 04:25:59 todoroki Exp $

.include <bsd.own.mk>
.include "../Makefile.inc"

LIST_S= common flashcfg bash dhcpd ifconfig modules named ppp pppoe \
	sendmail sshd vtund
INITRD_FS_SIZE= 32768

.include "${.CURDIR}/../../standard/initrd/Makefile.inc"

