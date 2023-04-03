#	$ssdlinux: Makefile,v 1.4 2002/06/20 11:45:47 kanoh Exp $

.include <bsd.own.mk>

PROG=		pppoe-server
SRCS=		${PROG}.c if.c debug.c common.c md5.c
MAN=		${PROG}.8

LDADD+=		-L${.CURDIR}/../libevent -levent
DPADD+=		${.CURDIR}/../libevent/libevent.a

NOGCCERROR=	yes

.include <bsd.prog.mk>
