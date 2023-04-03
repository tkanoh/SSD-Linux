#	$ssdlinux: Makefile,v 1.9 2004/10/01 05:39:36 yamagata Exp $

.include <bsd.own.mk>

PROG=		ntptimeset
SRCS=		${PROG}.c ntptime_config.c version.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/ntp
.PATH:		${DIST}/ntpdate

CPPFLAGS+=	-I${DIST}/ntpdate

LDADD+=		-L${.CURDIR}/../libntp -lntp
DPADD+=         ${.CURDIR}/../libntp/libntp.a

CLEANFILES=	version.c .version

version.c:
	${SHELL} ${.CURDIR}/../mkver ${PROG}

NOGCCERROR=	yes

.include <bsd.prog.mk>
