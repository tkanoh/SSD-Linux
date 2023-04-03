#	$ssdlinux: Makefile,v 1.4 2004/03/31 07:00:12 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	coreutils-
DISTVERSION=	5.0
ALTDISTNAME=	coreutils50
EXTRACT_SUFX=	tar.bz2
GNU_DIST=	yes
DEPENDENT=	lib/coreutils50
DEPENDENT+=	distrib/utils/libhack
DEPENDENT+=	distrib/utils/x_basename
DEPENDENT+=	distrib/utils/x_cat distrib/utils/x_chgrp distrib/utils/x_chmod
DEPENDENT+=	distrib/utils/x_chown distrib/utils/x_chroot distrib/utils/x_cp
DEPENDENT+=	distrib/utils/x_date distrib/utils/x_df distrib/utils/x_expr
DEPENDENT+=	distrib/utils/x_ln distrib/utils/x_ls
DEPENDENT+=	distrib/utils/x_mkdir distrib/utils/x_mv distrib/utils/x_rm
DEPENDENT+=	distrib/utils/x_touch
DEPENDENT+=	distrib/utils/x_sleep
DEPENDENT+=	distrib/i386/ramdiskbin/ramdiskbin.conf.in

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
