#	$ssdlinux: Makefile.inc,v 1.1.1.1 2002/05/02 13:37:13 kanoh Exp $

.include <bsd.own.mk>		# for LDSTATIC def'n

WARNS?=		0
BINDIR?=	/usr/sbin
#LDSTATIC?=	-static -s
WFORMAT?=	2
NONLS=		yes
