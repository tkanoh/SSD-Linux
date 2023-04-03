#	$ssdlinux: Makefile,v 1.18 2005/01/19 02:18:20 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	sendmail.
DISTVERSION=	8.13.3
MASTER_SITES=	ftp://ftp.sendmail.org/pub/sendmail
ALTRENAMEDISTDIR=	mv ${DISTDIR}/sendmail-${DISTVERSION} ${DISTDIR}/sendmail
LOCAL_PATCHFILES=	sendmail-8.13.3-close_wait.p2
DISTRELEASE=	2
DEPENDENT=	usr.sbin/sendmail
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/sendmail
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/sendmail

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
