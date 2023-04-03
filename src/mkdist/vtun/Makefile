#	$ssdlinux: Makefile,v 1.8 2004/12/15 08:35:27 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	vtun-
DISTVERSION=	2.6
MASTER_SITES=	http://telia.dl.sourceforge.net/sourceforge/vtun
# see also http://vtun.sourceforge.net
ALTRENAMEDISTDIR=	echo
DEPENDENT=	usr.sbin/vtund ditrib/utils/x_vtun etc/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/vtund
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/vtund

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
