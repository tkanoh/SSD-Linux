#	$ssdlinux: Makefile,v 1.10 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	coreutils-
DISTVERSION=	5.2.1
EXTRACT_SUFX=	tar.bz2
GNU_DIST=	yes
LOCAL_PATCHFILES=       uname_c.patch
DISTRELEASE=    1
DEPENDENT=	lib/coreutils
# fileutils
DEPENDENT+=	bin/chmod bin/cp bin/dd bin/ln bin/ls bin/mkdir bin/mv bin/rm 
DEPENDENT+=	bin/rmdir bin/sync bin/df 
DEPENDENT+=	sbin/mknod
DEPENDENT+=	usr.bin/chgrp usr.bin/dircolors usr.bin/du usr.bin/ginstall
DEPENDENT+=	usr.bin/dir usr.bin/vdir usr.bin/mkfifo usr.bin/shred
DEPENDENT+=	usr.bin/touch
DEPENDENT+=	usr.sbin/chown
##DEPENDENT+=	distrib/utils/x_chgrp
##DEPENDENT+=	distrib/utils/x_chown distrib/utils/x_chmod distrib/utils/x_cp
##DEPENDENT+=	distrib/utils/x_ln distrib/utils/x_ls distrib/utils/x_mkdir
##DEPENDENT+=	distrib/utils/x_mv distrib/utils/x_rm distrib/utils/x_df
DEPENDENT+=	cross/powerpc/ginstall
# textutils
DEPENDENT+=	bin/cat
DEPENDENT+=	usr.bin/cksum usr.bin/comm usr.bin/csplit usr.bin/cut
DEPENDENT+=	usr.bin/expand usr.bin/fmt usr.bin/fold usr.bin/head
DEPENDENT+=	usr.bin/join usr.bin/md5sum usr.bin/nl usr.bin/od 
DEPENDENT+=	usr.bin/paste usr.bin/pr usr.bin/ptx usr.bin/sha1sum
DEPENDENT+=	usr.bin/sort usr.bin/split usr.bin/sum usr.bin/tac usr.bin/tail
DEPENDENT+=	usr.bin/tr usr.bin/tsort usr.bin/unexpand usr.bin/uniq
DEPENDENT+=	usr.bin/wc
##DEPENDENT+=	distrib/utils/x_cat
# sh-utils
DEPENDENT+=	bin/date bin/echo bin/expr bin/hostname bin/pwd
DEPENDENT+=	bin/sleep bin/test bin/uname bin/stty
DEPENDENT+=	usr.bin/basename usr.bin/dirname usr.bin/env
DEPENDENT+=	usr.bin/factor usr.bin/false usr.bin/id
DEPENDENT+=	usr.bin/logname usr.bin/nohup usr.bin/pathchk usr.bin/pinky
DEPENDENT+=	usr.bin/printenv usr.bin/printf usr.bin/seq
DEPENDENT+=	usr.bin/tee usr.bin/true usr.bin/tty usr.bin/users
DEPENDENT+=	usr.bin/who usr.bin/whoami usr.bin/yes
DEPENDENT+=	usr.bin/hostid usr.bin/nice usr.bin/uptime
DEPENDENT+=	usr.sbin/chroot
##DEPENDENT+=	distrib/utils/x_chroot

##DEPENDENT+=	distrib/i386/ramdiskbin/ramdiskbin.conf.in
##DEPENDENT+=	distrib/utils/libhack
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/hotplug
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
