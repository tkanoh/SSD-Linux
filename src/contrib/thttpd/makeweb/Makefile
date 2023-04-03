#	$ssdlinux: Makefile,v 1.3 2004/06/07 09:20:35 yamagata Exp $

.include <bsd.own.mk>

PROG=		makeweb
BINGRP=		nogroup
BINMODE=	2555
	
THTTPDTOP=	${.CURDIR}/..
DIST=           ${.CURDIR}/../../../dist/thttpd
.PATH:		${DIST}/extras

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

LDSTATIC=	-static -s

.include <bsd.prog.mk>
