#	$ssdlinux: Makefile,v 1.2 2002/06/06 03:07:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		bootpd
SRCS=		${PROG}.c dovend.c readfile.c hash.c dumptab.c \
		lookup.c getif.c hwaddr.c tzone.c report.c
MAN=		${PROG}.8 bootptab.5

SCRIPTS=	bootptab
SCRIPTSDIR=	/etc

DIST=		${.CURDIR}/../../../dist/bootp
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST}

NOGCCERROR=	yes

.include <bsd.prog.mk>
