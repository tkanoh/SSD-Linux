#	$ssdlinux: Makefile,v 1.6 2004/05/19 03:56:26 yamagata Exp $

.include <bsd.own.mk>

PROG=		ntp-genkeys
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../../dist/ntp
.PATH:		${DIST}/util

CPPFLAGS+=	-I${DIST}/util

LDADD+=		${.CURDIR}/../ntpd/ntp_config.o
LDADD+=		-L${.CURDIR}/../libntp -lntp
DPADD+=         ${.CURDIR}/../libntp/libntp.a

${MAN}:
	perl ${.CURDIR}/../ntp-html2mdoc.pl ${.CURDIR}/genkeys.htm > ${.TARGET}

NOGCCERROR=	yes

.include <bsd.prog.mk>
