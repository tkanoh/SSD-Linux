#	$ssdlinux: Makefile,v 1.2 2002/06/06 03:07:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		bootpgw
SRCS=		${PROG}.c getif.c hwaddr.c report.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/bootp
.PATH:		../bootpd ${DIST}

CPPFLAGS+=	-I${DIST}

NOGCCERROR=	yes

.include <bsd.prog.mk>
