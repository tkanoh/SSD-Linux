#	$ssdlinux: Makefile,v 1.1 2002/11/08 07:30:41 yamagata Exp $

.include <bsd.own.mk>

PROG=		showconsolefont
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/kbd
.PATH:		${DIST}/src ${DIST}/man/man8

LIBKBDDIR=	${.CURDIR}/../../../lib/kbd

CPPFLAGS+=	-Wall -Wmissing-prototypes -Wstrict-prototypes
CPPFLAGS+=	-DDATADIR=\"/usr/share/kbd\" 
CPPFLAGS+=	-I${LIBKBDDIR} -I${LIBKBDDIR}/dummy
LDADD=		${LIBKBDDIR}/xmalloc.o
LDADD+=		${LIBKBDDIR}/getfd.o
LDADD+=		${LIBKBDDIR}/kdmapop.o
LDADD+=		${LIBKBDDIR}/kdfontop.o

.include <bsd.prog.mk>
