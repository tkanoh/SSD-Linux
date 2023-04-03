#	$ssdlinux: Makefile,v 1.3 2004/02/27 06:03:54 yamagata Exp $

.include <bsd.own.mk>

MAN=		ssh_config.5 sshd_config.5
FILES=		moduli ssh_config sshd_config
FILESMODE=	444
FILESDIR=	/etc/ssh

DIST=           ${.CURDIR}/../../../dist/openssh
.PATH:          ${DIST}

.include <bsd.prog.mk>
