#	$ssdlinux: Makefile,v 1.4 2002/08/01 12:46:37 kanoh Exp $

.include <bsd.own.mk>

PROG=		rndc
SRCS=		${PROG}.c util.c
MAN=		${PROG}.8 ${PROG}.conf.5

DIST=		${.CURDIR}/../../../dist/bind
.PATH:		${DIST}/bin/${PROG}

LIBBINDDIR=	${.CURDIR}/../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

CPPFLAGS+=	-I${DIST}/bin/named/include
CPPFLAGS+=	-DRNDC_SYSCONFDIR=\"/etc/namedb\"
CPPFLAGS+=	-DRNDC_CONFFILE=\"/etc/namedb/rndc.conf\"
CPPFLAGS+=	-DRNDC_KEYFILE=\"/etc/namedb/rndc.key\"

.include <bsd.prog.mk>
