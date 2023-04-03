#	$ssdlinux: Makefile,v 1.2 2002/06/04 06:23:34 yamagata Exp $

.include <bsd.own.mk>

PROG=		portmap
SRCS=		${PROG}.c pmap_check.c from_local.c daemon.c strerror.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/portmap
.PATH:		${DIST}

CPPFLAGS+=	-DFACILITY=LOG_DAEMON
CPPFLAGS+=	-DHOSTS_ACCESS
CPPFLAGS+=	-DCHECK_PORT
CPPFLAGS+=	-Dconst=
CPPFLAGS+=	-I${DIST}

WRAPDIR=	${.CURDIR}/../../lib/libwrap
LDADD+=		-L${WRAPDIR} -lwrap
DPADD+=		${WRAPDIR}/libwrap.a

.include <bsd.prog.mk>
