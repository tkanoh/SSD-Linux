#	$ssdlinux: Makefile,v 1.2 2002/06/04 06:20:41 yamagata Exp $

.include <bsd.own.mk>

PROG=		pmap_dump
MKMAN=		no

DIST=		${.CURDIR}/../../dist/portmap
.PATH:		${DIST}

CPPFLAGS+=	-DFACILITY=LOG_DAEMON
CPPFLAGS+=	-DHOSTS_ACCESS
CPPFLAGS+=	-DCHECK_PORT
CPPFLAGS+=	-Dconst=
CPPFLAGS+=	-I${DIST}

.include <bsd.prog.mk>
