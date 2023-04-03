#	$ssdlinux: Makefile,v 1.2 2002/06/06 07:16:54 yamagata Exp $

.include <bsd.own.mk>

PROG=		ripd
SRCS=		${PROG}.c rip_zebra.c rip_interface.c rip_debug.c \
		rip_snmp.c rip_routemap.c rip_peer.c rip_offset.c \
		rip_main.c
MAN=		${PROG}.8 ripngd.8

FILES=		${PROG}.conf.sample
FILESMODE=	600
FILESDIR=	/etc

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
