#	$ssdlinux: Makefile,v 1.9 2004/10/18 06:11:25 yamagata Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR= fingerd ftpd sftp-server ssh-keysign ssh-rand-helper identd uucp
SUBDIR+= postfix
SUBDIR+= expreserve exrecover
SUBDIR+= comsat rpc.rusersd rpc.rwalld talkd telnetd tftpd
SUBDIR+= rexecd rlogind rshd
SUBDIR+= rpc.rquotad
SUBDIR+= frcode code bigram
.else

SUBDIR= fingerd ftpd sftp-server ssh-keysign ssh-rand-helper identd uucp
.if ${MTA} == "postfix"
SUBDIR+= postfix
.endif

# ex
SUBDIR+= expreserve exrecover

# usagi-tool/src
SUBDIR+= comsat rpc.rusersd rpc.rwalld talkd telnetd tftpd

# usagi-tool/src/netkit-rsh
SUBDIR+= rexecd rlogind rshd

# nfs-utils
SUBDIR+= rpc.rquotad

# findutils
SUBDIR+= frcode code bigram

.endif

.include <bsd.subdir.mk>
