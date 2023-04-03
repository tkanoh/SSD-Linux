#	$ssdlinux: Makefile,v 1.19 2004/12/15 08:35:27 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	usagi-tool-
.if ${KERNEL_VERSION} == "2.4.20"
DISTVERSION=	stable-20030214
.else
DISTVERSION=	stable-20040104
.endif
USAGI_DIST=	yes
USAGI_RELEASE=	stable
#USAGI_RELEASE=	snap

ALTRENAMEDISTDIR= mv ${DISTDIR}/usagi ${DISTDIR}/usagi-tool 

LOCAL_PATCHFILES=	mii-tool_c.diff

DISTRELEASE=	3
DEPENDENT=	lib/libinet6 usr.bin/pfkey
DEPENDENT+=	usr.sbin/tracepath6 usr.sbin/traceroute6
# src/net-tools
DEPENDENT+=	lib/net-tools
DEPENDENT+=	sbin/ifconfig sbin/iptunnel
DEPENDENT+=	sbin/ipmaddr sbin/mii-tool sbin/nameif sbin/plipconfig
DEPENDENT+=	sbin/route sbin/slattach
DEPENDENT+=	usr.bin/netstat
DEPENDENT+=	usr.sbin/arp usr.sbin/rapr
# src/rtsol
DEPENDENT+=	bin/rtsol
# src/radvd
DEPENDENT+=	usr.sbin/radvd
# src/miplv6
DEPENDENT+=	usr.sbin/mipdiag  usr.sbin/ipv6tunnel
# src/tcp_warppers
DEPENDENT+=	lib/libwrap usr.sbin/tcpdchk usr.sbin/tcpdmatch
# src/netkit-rsh
DEPENDENT+=	bin/rcp bin/rexec
DEPENDENT+=	usr.bin/rlogin usr.bin/rsh
DEPENDENT+=	libexec/rexecd libexec/rlogind libexec/rshd
# src/sysklogd
DEPENDENT+=	usr.sbin/syslogd usr.sbin/klogd
# src/netkit-timed
DEPENDENT+=	usr.sbin/timed
DEPENDENT+=	linux
# src/netkit-routed
DEPENDENT+=	sbin/routed sbin/ripquery
# src/netkit-base
DEPENDENT+=	sbin/ping
# src/iputils
DEPENDENT+=	sbin/ping6
# src/iproute2
DEPENDENT+=	lib/iproute2
DEPENDENT+=	sbin/ip
DEPENDENT+=	usr.sbin/rtmon usr.sbin/rtacct usr.sbin/tc
# src/netkit-rwho
DEPENDENT+=	usr.bin/rwho usr.bin/ruptime usr.sbin/rwhod
# src/netkit-rusers
DEPENDENT+=	usr.bin/rusers usr.bin/rup libexec/rpc.rusersd
# src/biff+comsat
DEPENDENT+=	usr.bin/biff libexec/comsat
# src/netkit-bootparamd
DEPENDENT+=	usr.bin/callbootd usr.sbin/rpc.bootparamd
# src/bsd-finger
DEPENDENT+=	usr.bin/finger
# src/netkit-rwall
DEPENDENT+=	usr.bin/rwall libexec/rpc.rwalld
# src/netkit-ntalk
DEPENDENT+=	usr.bin/talk libexec/talkd
# src/netkit-telnet
DEPENDENT+=	usr.bin/telnet libexec/telnetd
# src/netkit-tftp
DEPENDENT+=	usr.bin/tftp libexec/tftpd
# src/netwrite
DEPENDENT+=	usr.bin/write usr.sbin/writed
# src/mkdtcp
DEPENDENT+=	usr.sbin/dtcpc

DEPENDENT+=	distrib/utils/libhack
DEPENDENT+=	distrib/utils/libnet-tools
DEPENDENT+=	distrib/utils/x_ifconfig
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/ipv6
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
