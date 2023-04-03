#	$ssdlinux: Makefile,v 1.4 2004/02/04 06:30:36 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR=		libiptc .WAIT iptables .WAIT iptables-save iptables-restore
SUBDIR+=	ip6tables
.else
SUBDIR=		libiptc .WAIT iptables .WAIT iptables-save iptables-restore
.if ${IPV6} == "yes"
SUBDIR+=	ip6tables
.endif
.endif

.include <bsd.subdir.mk>

