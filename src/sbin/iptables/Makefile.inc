#	$ssdlinux: Makefile.inc,v 1.1.1.1 2002/05/02 13:37:08 kanoh Exp $

.include <bsd.own.mk>

WARNS?=		0
BINDIR?=	/sbin
.if ${FULL_SHARED} != "yes"
LDSTATIC?=	-static -s
.endif
WFORMAT?=	2
NONLS=		yes
