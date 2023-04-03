#	$ssdlinux: Makefile.inc,v 1.1.1.1 2002/05/02 13:37:04 kanoh Exp $

.include <bsd.own.mk>		# for LDSTATIC def'n

WARNS?=		0
BINDIR?=	/bin
.if ${FULL_SHARED} != "yes"
LDSTATIC?=	-static -s
.endif
NONLS= yes
