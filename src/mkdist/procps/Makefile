#	$ssdlinux: Makefile,v 1.30 2005/01/27 02:38:42 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	procps-
DISTVERSION=	3.2.5
MASTER_SITES=	http://procps.sourceforge.net
# proc
# Check contents of shlib_version.
DEPENDENT=	lib/libproc
# ps
DEPENDENT=	bin/ps
#
DEPENDENT=	bin/kill 
DEPENDENT+=	usr.bin/free usr.bin/pmap usr.bin/pgrep usr.bin/skill
DEPENDENT+=	usr.bin/slabtop usr.bin/pwdx
DEPENDENT+=	usr.bin/tload usr.bin/top usr.bin/w usr.bin/watch
DEPENDENT+=	usr.sbin/sysctl usr.sbin/vmstat
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin
DEPENDENT+=	distrib/powerpc-obs50/initrd/list_in/common

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
