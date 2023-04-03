#	$ssdlinux: Makefile,v 1.3 2004/06/16 23:04:49 kanoh Exp $

.include <bsd.own.mk>

PROG=		ip
SRCS=		${PROG}.c ipaddress.c iproute.c iprule.c rtm_map.c iptunnel.c \
		ipneigh.c iplink.c ipmaddr.c ipmonitor.c ipmroute.c
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/src/iproute2/${PROG}
.PATH:		${DIST}

LIBIPROUTE2=	${.CURDIR}/../../lib/iproute2
.include "${LIBIPROUTE2}/Makefile.cflags"
.include "${LIBIPROUTE2}/Makefile.ldflags"

.include <bsd.prog.mk>
