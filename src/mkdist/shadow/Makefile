#	$ssdlinux: Makefile,v 1.16 2005/01/27 03:41:41 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	shadow-
DISTVERSION=	4.0.7
EXTRACT_SUFX=	tar.bz2
MASTER_SITES=	ftp://ftp.pld.org.pl/software/shadow
# lib and libmisc
DEPENDENT=	lib/shadow
# src
DEPENDENT+=	bin/login
DEPENDENT+=	sbin/sulogin
DEPENDENT+=	usr.bin/groups usr.bin/su
DEPENDENT+=	usr.bin/faillog usr.bin/lastlog usr.bin/chage usr.bin/chfn
DEPENDENT+=	usr.bin/chsh usr.bin/expiry usr.bin/gpasswd usr.bin/newgrp
DEPENDENT+=	usr.bin/passwd
DEPENDENT+=	usr.sbin/chpasswd usr.sbin/groupadd
DEPENDENT+=	usr.sbin/groupdel usr.sbin/groupmod usr.sbin/logoutd
DEPENDENT+=	usr.sbin/mkpasswd usr.sbin/newusers usr.sbin/useradd
DEPENDENT+=	usr.sbin/userdel usr.sbin/usermod usr.sbin/grpck usr.sbin/pwck
DEPENDENT+=	usr.sbin/vipw usr.sbin/grpconv usr.sbin/grpunconv
DEPENDENT+=	usr.sbin/pwconv usr.sbin/pwunconv
DEPENDENT+=	distrib/utils/libshadow-misc
DEPENDENT+=	distrib/utils/x_login distrib/utils/x_passwd
DEPENDENT+=	distrib/utils/x_su distrib/utils/x_sulogin
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/useradd
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
