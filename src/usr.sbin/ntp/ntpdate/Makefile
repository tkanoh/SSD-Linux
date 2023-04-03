#	$ssdlinux: Makefile,v 1.10 2004/05/19 03:55:28 yamagata Exp $

.include <bsd.own.mk>

PROG=		ntpdate
SRCS=		${PROG}.c version.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/ntp
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-I${DIST}/${PROG}

LDADD+=		-L${.CURDIR}/../libntp -lntp
DPADD+=         ${.CURDIR}/../libntp/libntp.a

CLEANFILES=	version.c .version ${MAN}

version.c:
	${SHELL} ${.CURDIR}/../mkver ${PROG}

${MAN}:
	perl ${.CURDIR}/../ntp-html2mdoc.pl ${.CURDIR}/${PROG}.htm > ${.TARGET}

NOGCCERROR=	yes

.include <bsd.prog.mk>
