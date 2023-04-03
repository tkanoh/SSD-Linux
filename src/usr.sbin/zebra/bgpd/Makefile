#	$ssdlinux: Makefile,v 1.3 2003/03/18 07:06:35 kanoh Exp $

.include <bsd.own.mk>

PROG=		bgpd
SRCS=		bgp_main.c bgpd.c bgp_fsm.c bgp_aspath.c bgp_community.c \
		bgp_attr.c bgp_debug.c bgp_route.c bgp_zebra.c bgp_open.c \
		bgp_routemap.c bgp_packet.c bgp_network.c bgp_filter.c \
		bgp_regex.c bgp_clist.c bgp_dump.c bgp_snmp.c bgp_ecommunity.c \
		bgp_mplsvpn.c bgp_nexthop.c bgp_damp.c bgp_table.c \
		bgp_advertise.c bgp_vty.c
MAN=		${PROG}.8

FILES=		${PROG}.conf.sample ${PROG}.conf.sample2
FILESMODE=	600
FILESDIR=	/etc

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-I${DIST}/${PROG}

NOGCCERROR=	yes

.include <bsd.prog.mk>
