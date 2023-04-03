#	$ssdlinux: Makefile,v 1.4 2004/03/06 15:59:19 yamagata Exp $

.include <bsd.own.mk>

.if defined(DESTDIR) || !make(install)
FILES=		pppoe-server-options pppoe.conf firewall-standalone firewall-masq
FILESDIR=	/etc/ppp
.endif
MAN=		pppoe.conf.5

.include <bsd.prog.mk>
