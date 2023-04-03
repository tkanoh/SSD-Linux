#	$ssdlinux: Makefile,v 1.1 2002/08/05 10:33:29 kanoh Exp $

.include <bsd.own.mk>

PROG=		rndc-confgen
SRCS=		rndc-confgen.c util.c os.c
MKMAN=		no
NO_SSL=		yes

DIST=		${.CURDIR}/../../../../dist/bind
.PATH:		${DIST}/bin/rndc ${DIST}/bin/rndc/unix

LDADD+=		-L${.CURDIR}/../libdns -ldns
DPADD+=		${.CURDIR}/../libdns/libdns.a

LIBBINDDIR=	${.CURDIR}/../../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

CPPFLAGS+=	-I${DIST}/bin/rndc/include
CPPFLAGS+=	-DRNDC_SYSCONFDIR=\"/etc/namedb/\"
CPPFLAGS+=	-DRNDC_CONFFILE=\"/etc/namedb/rndc.conf\"
CPPFLAGS+=	-DRNDC_KEYFILE=\"/etc/namedb/rndc.key\"

proginstall:

.include <bsd.prog.mk>
