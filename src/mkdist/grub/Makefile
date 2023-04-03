#	$ssdlinux: Makefile,v 1.9 2005/02/09 04:04:38 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	grub-
DISTVERSION=	0.96
MASTER_SITES=	ftp://alpha.gnu.org/gnu/grub
DEPENDENT=	usr.sbin/grub
DEPENDENT+=	distrib/utils/x_grub
DEPENDENT+=	distrib/i386/initrd/list.in.kernel
DEPENDENT+=	distrib/i386/initrd/list.in.no
DEPENDENT+=	distrib/i386/initrd/list.in.pcmcia-cs

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
