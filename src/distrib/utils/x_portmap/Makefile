#	$ssdlinux: Makefile,v 1.2 2002/06/12 01:20:51 yamagata Exp $

.include <bsd.own.mk>

PROG=		portmap
SRCS=		${PROG}.c pmap_check.c from_local.c daemon.c strerror.c
MKMAN=		no

PORTMAPDIR=	${.CURDIR}/../../../usr.sbin/${PROG}
DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${PORTMAPDIR} ${DIST}

CPPFLAGS+=	-DFACILITY=LOG_DAEMON
#CPPFLAGS+=	-DHOSTS_ACCESS
CPPFLAGS+=	-DCHECK_PORT
CPPFLAGS+=	-Dconst=
CPPFLAGS+=	-I${PORTMAPDIR} -I${DIST}

#WRAPDIR=	${.CURDIR}/../../lib/libwrap
#LDADD+=	-L${WRAPDIR} -lwrap
#DPADD+=	${WRAPDIR}/libwrap.a

.include <bsd.prog.mk>
