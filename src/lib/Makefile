#	$ssdlinux: Makefile,v 1.16 2005/02/10 09:04:18 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR+=	glibc ssl libz libdb libdb1 pam gmp libtermcap libncurses
SUBDIR+=	libbz2 kbd libproc libwrap modules iptables ssh
SUBDIR+=	dhcp  dump coreutils util-linux libinet6 net-tools
SUBDIR+=	iproute2 findutils  bind  postfix e2fsprogs modutils
SUBDIR+=	nfs-utils readline shadow uucp libiw libfl glibc-static
SUBDIR+=	libpng firmware libusb
.else
	
.ifndef BUILD_WORLD
SUBDIR+= glibc
SUBDIR+= ssl
SUBDIR+= libz
SUBDIR+= libdb
.if ${USE_PAM} == "yes"
SUBDIR+= pam
.endif
.endif

SUBDIR+= gmp
SUBDIR+= libtermcap
SUBDIR+= libncurses
SUBDIR+= libdb1
SUBDIR+= libbz2 kbd libproc libwrap modules
SUBDIR+= iptables
SUBDIR+= ssh
SUBDIR+= dhcp
SUBDIR+= e2fsprogs
SUBDIR+= dump
SUBDIR+= coreutils
SUBDIR+= util-linux

# usagi-tool/src
.if ${IPV6} == "yes"
SUBDIR+= libinet6
.endif
SUBDIR+= net-tools
SUBDIR+= iproute2

SUBDIR+= findutils
SUBDIR+= bind
.if ${MTA} == "postfix"
SUBDIR+= postfix
.endif
SUBDIR+= modutils
SUBDIR+= nfs-utils
SUBDIR+= readline	
SUBDIR+= shadow	
SUBDIR+= uucp
SUBDIR+= libiw
SUBDIR+= libfl

.if ${WITH_X11} == "yes"
SUBDIR+= libpng
.endif

.if ${USE_PCMCIA} == "kernel"
SUBDIR+= firmware
.endif

.if ${TARGET_HOSTTYPE} == "i386"
SUBDIR+= glibc-static
.endif

.if ${KERNEL_VERSION} != "2.4.20"
SUBDIR+= libusb
.endif

.endif

.include <bsd.subdir.mk>
