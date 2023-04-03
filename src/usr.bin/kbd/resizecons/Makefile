#	$ssdlinux: Makefile,v 1.3 2002/11/08 07:26:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		resizecons
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/kbd
.PATH:		${DIST}/src ${DIST}/man/man8

LIBKBDDIR=	${.CURDIR}/../../../lib/kbd

CPPFLAGS+=	-Wall -Wmissing-prototypes -Wstrict-prototypes
CPPFLAGS+=	-DDATADIR=\"/usr/share/kbd\" 
CPPFLAGS+=	-I${LIBKBDDIR}/kbd -I${LIBKBDDIR}/dummy
LDADD=		${LIBKBDDIR}/findfile.o
LDADD+=		${LIBKBDDIR}/xmalloc.o
LDADD+=		${LIBKBDDIR}/getfd.o

.include <bsd.prog.mk>
