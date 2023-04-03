#	$ssdlinux: Makefile,v 1.3 2002/11/08 07:24:17 yamagata Exp $

.include <bsd.own.mk>

PROG=		getkeycodes
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/kbd
.PATH:		${DIST}/src ${DIST}/man/man8

LIBKBDDIR=	${.CURDIR}/../../../lib/kbd

CPPFLAGS+=	-Wall -Wmissing-prototypes -Wstrict-prototypes
CPPFLAGS+=	-DDATADIR=\"/usr/share/kbd\" 
CPPFLAGS+=	-I${LIBKBDDIR} -I${LIBKBDDIR}/dummy
LDADD=		${LIBKBDDIR}/getfd.o

.include <bsd.prog.mk>
