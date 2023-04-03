#	$ssdlinux: Makefile,v 1.40 2005/02/10 09:04:18 todoroki Exp $

.include <bsd.own.mk>

TARGETS+=	versions_file

.ifmake clean
SUBDIR=		Linux-PAM autoconf automake \
		bash bc bind binutils bison bootp bzip2 \
		coreutils cron cvs db dhcp diffutils dump e2fsprogs ed ex \
		file findutils flex \
		gawk gcc gdb gettext glibc gmp grep groff grub gzip \
		iptables \
		kbd kernel ksymoops \
		less libtool libusb lpr tnftp tnftpd \
		m4 make man man-pages modutils \
		newsyslog ncurses nfs-utils ntp \
		openssh openssl ov511 \
		patch pciutils pcmcia-cs perl pidentd portmap \
		ppc-headers ppp procinfo procps psmisc \
		readline rp-pppoe rsync \
		screen sed setserial shadow strace sudo sysvinit \
		tar termcap texinfo \
		updated usagi-tool usbutils util-linux uucp \
		vtun wireless_tools zebra zlib
SUBDIR+=	sendmail
SUBDIR+=	postfix
SUBDIR+=	thttpd samba netatalk
SUBDIR+=	coreutils50
SUBDIR+=	libpng
SUBDIR+=	hotplug
SUBDIR+=	madwifi
.else

SUBDIR=		Linux-PAM autoconf automake \
		bash bc bind binutils bison bootp bzip2 \
		coreutils cron cvs db dhcp diffutils dump e2fsprogs ed ex \
		file findutils flex \
		gawk gcc gdb gettext glibc gmp grep groff grub gzip \
		iptables \
		kbd kernel ksymoops \
		less libtool lpr tnftp tnftpd \
		m4 make man man-pages modutils \
		newsyslog ncurses nfs-utils ntp \
		openssh openssl ov511 \
		patch pcmcia-cs perl pidentd portmap \
		ppc-headers ppp procinfo procps psmisc \
		readline rp-pppoe rsync \
		screen sed setserial shadow strace sudo sysvinit \
		tar termcap texinfo \
		updated usagi-tool util-linux uucp \
		vtun wireless_tools zebra zlib

.if ${MTA} == "sendmail"
SUBDIR+=	sendmail
.elif ${MTA} == "postfix"
SUBDIR+=	postfix
.endif

SUBDIR+=	thttpd samba netatalk
SUBDIR+=        coreutils50

.if ${WITH_X11} == "yes"
SUBDIR+=        libpng
.endif

.if ${KERNEL_VERSION} != "2.4.20"
SUBDIR+=	hotplug pciutils libusb usbutils
.if ${USE_PCMCIA} == "kernel"
SUBDIR+=	madwifi
.endif
.endif

.endif

.include <bsd.subdir.mk>
