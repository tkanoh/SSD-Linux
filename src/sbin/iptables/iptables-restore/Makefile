#	$ssdlinux: Makefile,v 1.2 2003/08/06 09:01:49 yamagata Exp $

.include <bsd.own.mk>

PROG=		iptables-restore
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/iptables
.PATH:		${DIST}

.include "${.CURDIR}/../../../lib/iptables/Makefile.cflags"

CPPFLAGS+=	-DIPT_LIB_DIR=\"${IPT_LIB_DIR}\"

LDADD+=		${.CURDIR}/../iptables/iptables.o
.if defined(STATIC_IPT)
CPPFLAGS+=	-DNO_SHARED_LIBS=1
LDSTATIC=	-static
LDADD+=		-L${.CURDIR}/../../../lib/iptables/libext -lext
DPADD+=		${.CURDIR}/../../../lib/iptables/libext/libext.a
.else
CPPFLAGS+=	-rdynamic
.endif

DPADD+=         ${.CURDIR}/../libiptc/libiptc.a
LDADD+=         -L${.CURDIR}/../libiptc -liptc
LDADD+=		-ldl -lnsl

.include <bsd.prog.mk>
