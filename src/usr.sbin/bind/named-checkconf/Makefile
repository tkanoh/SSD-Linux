#	$ssdlinux: Makefile,v 1.3 2002/08/01 12:48:05 kanoh Exp $

.include <bsd.own.mk>

PROG=		named-checkconf
SRCS=		${PROG}.c check-tool.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/bind
.PATH:		${DIST}/bin/check

LIBBINDDIR=	${.CURDIR}/../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

CPPFLAGS+=	-DNAMED_CONFFILE=\"/etc/namedb/named.conf\"

.include <bsd.prog.mk>
