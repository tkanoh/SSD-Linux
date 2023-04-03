#	$ssdlinux: Makefile,v 1.2 2002/06/06 03:07:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		bootpef
SRCS=		${PROG}.c dovend.c readfile.c hash.c dumptab.c \
		lookup.c hwaddr.c tzone.c report.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/bootp
.PATH:		../bootpd ${DIST}

CPPFLAGS+=	-I${DIST}

NOGCCERROR=	yes

.include <bsd.prog.mk>
