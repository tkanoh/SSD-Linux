#	$ssdlinux: Makefile,v 1.14 2004/11/12 15:22:12 kanoh Exp $

.include <bsd.own.mk>

SCRIPTS=	rc.conf rc.lkm rc.local rc.serial \
		rc.single rc.subr rc.sysinit gshadow netstart inetd.conf
SCRIPTSDIR=	/etc
SCRIPTSMODE=	555

FILES=		daily daily.conf dhclient.conf.sample dhcpd.conf.sample \
		dumpdates \
		ftpchroot ftpusers group hosts hosts.allow hosts.deny \
		ld.so.conf lkm.conf login.defs \
		man.conf monthly monthly.conf motd \
		newsyslog.conf nsswitch.conf ntp.conf \
		phones primes printcap profile protocols \
		remote \
		serial.conf services shells syslog.conf \
		termcap \
		usermgmt.conf \
		weekly weekly.conf
FILESMODE=	444
FILESDIR=	/etc

.if ${USE_PCMCIA} != "no"
SCRIPTS+=	rc.pcmcia
.endif

.if ${USE_PAM} == "yes"
FILES+=		pam.conf
.endif

inetd.conf: inetd.conf.in
.if ${IPV6} == "yes"
	sed -e 's|@TCP@|tcp6|g' -e 's|@UDP@|udp6|g' inetd.conf.in > inetd.conf 
.else
	sed -e 's|@TCP@|tcp|g' -e 's|@UDP@|udp|g' inetd.conf.in > inetd.conf 
.endif

rc.pcmcia: rc.pcmcia.${USE_PCMCIA}
	cp rc.pcmcia.${USE_PCMCIA} rc.pcmcia

CLEANFILES=	inetd.conf rc.pcmcia

scriptsinstall:
	${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${SCRIPTS} ${DESTDIR}${SCRIPTSDIR}
	chmod 600 ${DESTDIR}${SCRIPTSDIR}/gshadow
	chmod 444 ${DESTDIR}${SCRIPTSDIR}/inetd.conf
	ln -sf /usr/share/zoneinfo/Asia/Tokyo ${DESTDIR}${SCRIPTSDIR}/localtime

.include <bsd.prog.mk>

SUBDIR=		defaults mail namedb ssh

.include <bsd.subdir.mk>
