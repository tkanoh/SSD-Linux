#	$ssdlinux: Makefile,v 1.3 2004/06/07 09:25:20 yamagata Exp $

.include <bsd.own.mk>

PROG=		redirect
MAN=		${PROG}.8
	
THTTPDTOP=	${.CURDIR}/../..
DIST=           ${.CURDIR}/../../../../dist/thttpd
.PATH:		${DIST}/cgi-src

.include "${.CURDIR}/../../Makefile.cflags"
.include "${.CURDIR}/../../Makefile.ldflags"

.include <bsd.prog.mk>
