#	$ssdlinux: Makefile,v 1.4 2002/12/21 13:17:27 kanoh Exp $

.include <bsd.own.mk>

PROG=		tcpdmatch
SRCS=		${PROG}.c fakelog.c inetcf.c scaffold.c
MAN=		${PROG}.8
LDADD=		-L${.CURDIR}/../../lib/libwrap -lwrap
DPADD=		${.CURDIR}/../../lib/libwrap/libwrap.a

DIST=		${.CURDIR}/../../dist/usagi-tool/src/tcp_wrappers
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${.CURDIR}/../../lib/libinet6/Makefile.cflags"
.include "${.CURDIR}/../../lib/libwrap/Makefile.cflags"
.include "${.CURDIR}/../../lib/libinet6/Makefile.ldflags"

.include <bsd.prog.mk>
