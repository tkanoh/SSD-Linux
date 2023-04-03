#	$ssdlinux: Makefile,v 1.22 2005/03/10 05:12:14 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	openssh-
DISTVERSION=	4.0p1
MASTER_SITES=	ftp://ftp.openbsd.org/pub/OpenBSD/OpenSSH/portable
DEPENDENT=	lib/ssh usr.bin/ssh usr.sbin/sshd
DEPENDENT+=	libexec/sftp-server libexec/ssh-keysign libexec/ssh-rand-helper
DEPENDENT+=	etc/common/ssh
DEPENDENT+=	distrib/utils/x_sshd
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/sshd
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/sshd

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
