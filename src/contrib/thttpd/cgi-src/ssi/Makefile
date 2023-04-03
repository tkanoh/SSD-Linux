#	$ssdlinux: Makefile,v 1.3 2004/06/07 09:26:54 yamagata Exp $

.include <bsd.own.mk>

PROG=		ssi
MAN=		${PROG}.8
	
THTTPDTOP=	${.CURDIR}/../..
DIST=           ${.CURDIR}/../../../../dist/thttpd
.PATH:		${DIST}/cgi-src

.include "${.CURDIR}/../../Makefile.cflags"
.include "${.CURDIR}/../../Makefile.ldflags"

LDADD+=		${THTTPDTOP}/thttpd/match.o

.include <bsd.prog.mk>
