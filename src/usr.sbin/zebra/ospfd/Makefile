#	$ssdlinux: Makefile,v 1.3 2003/03/18 07:06:35 kanoh Exp $

.include <bsd.own.mk>

PROG=		ospfd
SRCS=		ospf_main.c ospfd.c ospf_zebra.c ospf_interface.c \
		ospf_ism.c ospf_neighbor.c ospf_nsm.c ospf_dump.c \
		ospf_network.c ospf_packet.c ospf_lsa.c ospf_spf.c \
		ospf_route.c ospf_ase.c ospf_abr.c ospf_ia.c \
		ospf_flood.c ospf_lsdb.c ospf_asbr.c ospf_routemap.c \
		ospf_snmp.c ospf_opaque.c ospf_te.c ospf_vty.c
MAN=		${PROG}.8 ospf6d.8

FILES=		${PROG}.conf.sample
FILESMODE=	600
FILESDIR=	/etc

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
