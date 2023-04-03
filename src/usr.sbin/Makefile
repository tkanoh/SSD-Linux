#	$ssdlinux: Makefile,v 1.33 2004/11/08 03:24:33 yamagata Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR+= arp badblocks bind bootp chown chpasswd chroot cron
SUBDIR+= dhcp-cltest dhcpd dhcp-svtest dhcrelay dtcpc
SUBDIR+= exportfs flashcfg freeramdisk groupadd groupdel groupmod
SUBDIR+= grpck grpconv grpunconv grub inetd ipv6tunnel iwevent ifrename
SUBDIR+= iwgetid iwlist iwpriv iwspy klogd logoutd lpr makewhatis
SUBDIR+= mipdiag mkpasswd mountd newusers nfsd ntp omshell
SUBDIR+= pciutils pmap_dump
SUBDIR+= pmap_set portmap postfix ppp pppoe pshd pwck pwconv pwunconv
SUBDIR+= radvd rapr rdev readprofile rpc.bootparamd rpc.lockd
SUBDIR+= rpc.statd rtacct rtmon runled rwhod sendmail sshd sysctl
SUBDIR+= syslogd tc tcpdchk tcpdmatch tcpdwl timed tracepath6
SUBDIR+= traceroute traceroute6 tunelp useradd userdel usermod
SUBDIR+= usbutils vipw visudo vmstat vtund writed zebra
.else

# usagi-tool/src
SUBDIR+= rpc.bootparamd timed writed rwhod dtcpc

# procps
SUBDIR+= sysctl vmstat

# portmap
SUBDIR+= portmap pmap_dump pmap_set

# util-linux/sys-utils
SUBDIR+= readprofile tunelp rdev

# man
SUBDIR+= makewhatis

# dhcp
SUBDIR+= dhcpd dhcrelay omshell dhcp-cltest dhcp-svtest

# usagi-tool/src/tcp_warppers
SUBDIR+= tcpdchk tcpdmatch

# usagi-tool/src/net-tools
SUBDIR+= arp rapr

# shadow
SUBDIR+= chpasswd groupadd groupdel groupmod logoutd
SUBDIR+= mkpasswd newusers useradd userdel usermod grpck pwck
SUBDIR+= vipw grpconv grpunconv pwconv pwunconv

# sudo
SUBDIR+= visudo

# e2fsprogs
SUBDIR+= badblocks

# coreutils(fileutils)
SUBDIR+= chown

# coreutils(sh-utils)
SUBDIR+= chroot

# nfs-utils
SUBDIR+= exportfs mountd nfsd rpc.lockd rpc.statd

# wireless_tools
SUBDIR+= iwlist iwpriv iwspy iwgetid iwevent ifrename

# ppp
SUBDIR+= ppp

# rp-pppoe
SUBDIR+= pppoe

.if ${IPV6} == "yes"
# usagi-tool/src/miplv6
SUBDIR+= # mipdiag ipv6tunnel
# usagi-tool/usagi/tracepath6
SUBDIR+= tracepath6
# usagi-tool/usagi/traceroute6
SUBDIR+= traceroute6
#usagi-tool/src/iproute2
SUBDIR+= rtmon rtacct tc
# usagi-tool/src/radvd
SUBDIR+= radvd
.endif

# printer daemon
SUBDIR+= lpr

.if ${TARGET_HOSTTYPE} == "i386"
SUBDIR+= grub
.elif ${TARGET_SSDHOSTTYPEX} == "powerpc-obs50" || ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
SUBDIR+= flashcfg pshd runled
.endif

SUBDIR+= tcpdwl
SUBDIR+= syslogd klogd
SUBDIR+=  bind bootp cron inetd ntp sshd freeramdisk

.if ${MTA} == "sendmail"
SUBDIR+=	sendmail
.elif ${MTA} == "postfix"
SUBDIR+=	postfix
.endif

SUBDIR+=  traceroute vtund zebra

.if ${KERNEL_VERSION} != "2.4.20"
SUBDIR+=  pciutils usbutils
.endif

.endif

.include <bsd.subdir.mk>
