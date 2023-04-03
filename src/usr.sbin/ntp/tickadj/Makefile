#	$ssdlinux: Makefile,v 1.9 2004/05/19 03:50:52 yamagata Exp $

.include <bsd.own.mk>

PROG=		tickadj
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../../dist/ntp
.PATH:		${DIST}/util

CPPFLAGS+=	-I${DIST}/util

LDADD+=		-L${.CURDIR}/../libntp -lntp
DPADD+=         ${.CURDIR}/../libntp/libntp.a

${MAN}:
	perl ${.CURDIR}/../ntp-html2mdoc.pl ${.CURDIR}/${PROG}.htm > ${.TARGET}

NOGCCERROR=	yes

.include <bsd.prog.mk>
