#	$ssdlinux: Makefile,v 1.52 2004/12/09 07:14:20 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR+= binutils gcc autoconf automake bison bmake crunch
SUBDIR+= flex libtool make mkdep patch ksymoops gdb
SUBDIR+= pcmcia-cs psmisc bc bind crontab cvs ex file \
        ftp gawk gettext grep groff gzip \
        kbd less m4 mail mktemp newsyslog openssl procinfo \
        rcs rsync screen sed shar ssh sudo \
        tar texinfo which \
        uuencode uudecode
SUBDIR+= uucp yacc perl biff callbootd finger rwall talk telnet tftp write
SUBDIR+= rwho ruptime rusers rup last mesg wall
SUBDIR+= free pgrep pmap skill slabtop pwdx tload top w watch
SUBDIR+= bzip2 bzip2recover bzgrep bzmore bzdiff
SUBDIR+= apropos man whatis getopt
SUBDIR+= fdformat isosize setfdprm raw
SUBDIR+= cal chkdupexe ddate logger look mcookie namei
SUBDIR+= rename script whereis setterm
SUBDIR+= arch cytune flock ipcrm ipcs renice setsid
SUBDIR+= col colcrt colrm column hexdump rev line tailf pg more ul
SUBDIR+=  cksum comm csplit cut expand fmt fold head join \
          md5sum nl od paste pr ptx sha1sum sort split sum tac tail \
          tr tsort unexpand uniq wc
SUBDIR+= cmp diff diff3 sdiff
SUBDIR+= find xargs locate
SUBDIR+= rlogin rsh netstat
SUBDIR+= chgrp dircolors du ginstall dir vdir mkfifo shred touch
SUBDIR+= basename dirname env factor false \
         id logname nohup pathchk pinky printenv printf seq \
         tee true tty users who whoami yes hostid nice uptime
SUBDIR+= groups su
SUBDIR+= faillog lastlog chage chfn chsh expiry gpasswd newgrp passwd
SUBDIR+= nfsstat resize
SUBDIR+= strace
SUBDIR+= tip
#SUBDIR+= pfkey
.else

.ifdef DEVELOPTOOLS
.ifndef BUILD_WORLD
SUBDIR+= binutils
SUBDIR+= gcc
.endif
SUBDIR+= autoconf automake bison bmake crunch 
SUBDIR+= flex libtool make mkdep patch
.if !defined(NEW_GLIBC)
SUBDIR+= ksymoops
.endif
.if !defined(NEW_GLIBC)
SUBDIR+= gdb
.endif
.if ${USE_PCMCIA} != "no"
SUBDIR+= pcmcia-cs
SUBDIR+= psmisc
.endif
.endif

SUBDIR+= bc bind crontab cvs ex file \
	ftp gawk gettext grep groff gzip \
	kbd less m4 mail mktemp newsyslog openssl procinfo \
	rcs rsync screen sed shar ssh sudo \
	tar texinfo which \
	uuencode uudecode
SUBDIR+= uucp
SUBDIR+= yacc

.if (!defined(NEW_GLIBC) && !defined(CROSS_BUILD)) || defined(CROSS_BUILD_PERL)
SUBDIR+= perl 
.endif

# usagi-tool/src
SUBDIR+= biff callbootd finger rwall talk telnet tftp write

# usagi-tool/src/netkit-rwho
SUBDIR+= rwho ruptime

# usagi-tool/src/netkit-rusers
SUBDIR+= rusers rup

#sysvinit
SUBDIR+= last mesg wall

# procps
SUBDIR+= free pgrep pmap skill tload top w watch slabtop pwdx

# bzip2
SUBDIR+= bzip2 bzip2recover bzgrep bzmore bzdiff

# man
SUBDIR+= apropos man whatis

# util-linux
#   getopt
SUBDIR+= getopt 
#   disk-utils
SUBDIR+= fdformat isosize setfdprm raw
#   misc-utils
SUBDIR+= cal chkdupexe ddate logger look mcookie namei rename script whereis \
	setterm
#   sys-utils
SUBDIR+= arch cytune flock ipcrm ipcs renice setsid 
#   text-utils
SUBDIR+= col colcrt colrm column hexdump rev line tailf pg more ul 

# textutils
SUBDIR+=  cksum comm csplit cut expand fmt fold head join \
	  md5sum nl od paste pr ptx sha1sum sort split sum tac tail \
	  tr tsort unexpand uniq wc

# diffutils
SUBDIR+= cmp diff diff3 sdiff

# findutils
SUBDIR+= find xargs locate

# usagi-tool/src/netkit-rsh
SUBDIR+= rlogin rsh

# usagi-tool/src/net-tools
SUBDIR+= netstat

# coreutils(fileutils)
SUBDIR+= chgrp dircolors du ginstall dir vdir mkfifo shred touch

# coreutils(sh-utils)
SUBDIR+= basename dirname env factor false \
	 id logname nohup pathchk pinky printenv printf seq \
	 tee true tty users who whoami yes hostid nice uptime

# shadow
SUBDIR+= groups su
SUBDIR+= faillog lastlog chage chfn chsh expiry gpasswd newgrp passwd

# nfs-utils
SUBDIR+= nfsstat

# XFree86 4.1.0 xc/programs/xterm
SUBDIR+= resize

SUBDIR+= strace
SUBDIR+= tip

.if ${IPV6} == "yes"
#usagi-tool/usagi/pfkey_util
#SUBDIR+= pfkey
.endif

.endif

.include <bsd.subdir.mk>
