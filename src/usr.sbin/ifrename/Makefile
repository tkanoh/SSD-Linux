#	$ssdlinux: Makefile,v 1.1 2004/11/08 03:24:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		ifrename
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/wireless_tools
.PATH:		${DIST}

.include "${.CURDIR}/../../lib/libiw/Makefile.cflags"
.include "${.CURDIR}/../../lib/libiw/Makefile.ldflags"

.include <bsd.prog.mk>
