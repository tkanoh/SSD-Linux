#	$ssdlinux: Makefile,v 1.4 2002/08/02 01:44:18 kanoh Exp $

.include <bsd.own.mk>

PROG=		rndc-confgen
SRCS=		rndc-confgen.c util.c os.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/bind
.PATH:		${DIST}/bin/rndc ${DIST}/bin/rndc/unix

LIBBINDDIR=	${.CURDIR}/../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

CPPFLAGS+=	-I${DIST}/bin/rndc/include
CPPFLAGS+=	-DRNDC_SYSCONFDIR=\"/etc/namedb/\"
CPPFLAGS+=	-DRNDC_CONFFILE=\"/etc/namedb/rndc.conf\"
CPPFLAGS+=	-DRNDC_KEYFILE=\"/etc/namedb/rndc.key\"

.include <bsd.prog.mk>
