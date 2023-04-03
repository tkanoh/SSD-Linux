#	$ssdlinux: Makefile,v 1.3 2003/11/29 15:53:33 kanoh Exp $

.include <bsd.own.mk>

PROG=		ripngd
SRCS=		ripng_main.c ripng_interface.c ripngd.c ripng_zebra.c \
		ripng_route.c ripng_debug.c ripng_routemap.c ripng_ifrmap.c
MAN=		${PROG}.8

FILES=		${PROG}.conf.sample
FILESMODE=	600
FILESDIR=	/etc

DIST=		${.CURDIR}/../../../dist/zebra
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
