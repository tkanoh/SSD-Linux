#	$ssdlinux: Makefile,v 1.3 2002/10/31 03:31:01 yamagata Exp $

.include <bsd.own.mk>

PROG=		iwlist
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/wireless_tools
.PATH:		${DIST}

.include "${.CURDIR}/../../lib/libiw/Makefile.cflags"
.include "${.CURDIR}/../../lib/libiw/Makefile.ldflags"

.include <bsd.prog.mk>
