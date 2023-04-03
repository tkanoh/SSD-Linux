#	$ssdlinux: Makefile,v 1.5 2003/11/29 15:53:33 kanoh Exp $

.include <bsd.own.mk>

PROG=		zebra
SRCS=		zserv.c main.c interface.c connected.c ioctl.c \
		zebra_rib.c redistribute.c debug.c rtadv.c zebra_snmp.c \
		zebra_vty.c ipforward_proc.c if_netlink.c if_proc.c \
		rt_netlink.c rtread_netlink.c
MAN=		${PROG}.8

FILES=		${PROG}.conf.sample
FILESMODE=	600
FILESDIR=	/etc

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
