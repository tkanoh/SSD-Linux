#	$ssdlinux: Makefile,v 1.3 2004/06/07 09:21:58 yamagata Exp $

.include <bsd.own.mk>

PROG=		htpasswd
	
THTTPDTOP=	${.CURDIR}/..
DIST=           ${.CURDIR}/../../../dist/thttpd
.PATH:		${DIST}/extras

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

.include <bsd.prog.mk>
