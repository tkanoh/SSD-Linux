#	$ssdlinux: Makefile,v 1.3 2002/10/08 03:21:29 yamagata Exp $

.include <bsd.own.mk>

PROG=		wall

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -I${DIST}/src
LDADD+=		${.CURDIR}/../../sbin/shutdown/dowall.o

.include <bsd.prog.mk>
