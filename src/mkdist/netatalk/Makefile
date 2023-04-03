#	$ssdlinux: Makefile,v 1.6 2004/12/15 08:35:25 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	netatalk-
DISTVERSION=	1.5.5
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	http://telia.dl.sourceforge.net/sourceforge/netatalk
# see also http://netatalk.sourceforge.net
LOCAL_PATCHFILES= ${DISTNAME}${DISTVERSION}.diff
DEPENDENT=	contrib/netatalk
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/netatalk
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/netatalk

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
