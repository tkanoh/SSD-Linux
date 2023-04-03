#	$ssdlinux: Makefile,v 1.1 2002/06/11 06:07:27 kanoh Exp $

.include <bsd.own.mk>

FILES=		127 localhost loopback.v6 named.conf root.cache
FILESMODE=	444
FILESDIR=	/etc/namedb

SYMLINKS+=	${FILESDIR}/named.conf /etc/named.conf

.include <bsd.prog.mk>
