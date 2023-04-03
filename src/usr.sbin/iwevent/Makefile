#	$ssdlinux: Makefile,v 1.1 2002/10/31 03:29:20 yamagata Exp $

.include <bsd.own.mk>

PROG=		iwevent
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/wireless_tools
.PATH:		${DIST}

.include "${.CURDIR}/../../lib/libiw/Makefile.cflags"
.include "${.CURDIR}/../../lib/libiw/Makefile.ldflags"

.include <bsd.prog.mk>
