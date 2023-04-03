#	$ssdlinux: Makefile,v 1.2 2004/12/14 04:25:58 todoroki Exp $

.include <bsd.own.mk>
.include "../Makefile.inc"

LIST_S=		common flashcfg sh zebra sshd

REQUIREMENT=	(cd ${SRCTOPDIR}/distrib/utils/x_sshd && bmake)

.include "${.CURDIR}/../../standard/initrd/Makefile.inc"
