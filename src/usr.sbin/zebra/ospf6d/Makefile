#	$ssdlinux: Makefile,v 1.3 2003/11/29 15:53:33 kanoh Exp $

.include <bsd.own.mk>

PROG=		ospf6d
SRCS=		ospf6_main.c ospf6_dump.c ospf6d.c ospf6_interface.c \
		ospf6_network.c ospf6_neighbor.c ospf6_message.c \
		ospf6_lsa.c ospf6_spf.c ospf6_route.c ospf6_zebra.c \
		ospf6_ism.c ospf6_dbex.c ospf6_lsdb.c ospf6_prefix.c \
		ospf6_top.c ospf6_area.c ospf6_nsm.c ospf6_routemap.c \
		ospf6_proto.c ospf6_hook.c ospf6_asbr.c ospf6_bintree.c \
		ospf6_linklist.c ospf6_abr.c ospf6_intra.c ospf6_damp.c
MAN=		${PROG}.8

FILES=		${PROG}.conf.sample
FILESMODE=	600
FILESDIR=	/etc

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
