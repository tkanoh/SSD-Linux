#	$ssdlinux: Makefile,v 1.3 2002/06/06 02:31:21 yamagata Exp $

.include <bsd.own.mk>

PROG=		utmpdump
MKMAN=		no

DIST=		${.CURDIR}/../../dist/sysvinit
.PATH:		${DIST}/src ${DIST}/man

CPPFLAGS+=	-Wall -D_GNU_SOURCE -I${DIST}/src

.include <bsd.prog.mk>
