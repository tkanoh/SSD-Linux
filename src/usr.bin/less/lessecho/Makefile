#	$ssdlinux: Makefile,v 1.1 2002/07/04 01:02:49 yamagata Exp $

.include <bsd.own.mk>

PROG=		lessecho
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/less
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}/../less

LDADD+=		${.CURDIR}/../less/version.o

.include <bsd.prog.mk>
