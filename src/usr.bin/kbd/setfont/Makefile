#	$ssdlinux: Makefile,v 1.3 2002/11/08 07:27:40 yamagata Exp $

.include <bsd.own.mk>

PROG=		setfont
MAN=		${PROG}.8
CLEANFILES=     ${MAN}

DIST=		${.CURDIR}/../../../dist/kbd
.PATH:		${DIST}/src

LIBKBDDIR=	${.CURDIR}/../../../lib/kbd

CPPFLAGS+=	-Wall -Wmissing-prototypes -Wstrict-prototypes
CPPFLAGS+=	-DDATADIR=\"/usr/share/kbd\" 
CPPFLAGS+=	-I${LIBKBDDIR} -I${LIBKBDDIR}/dummy
LDADD=		${LIBKBDDIR}/findfile.o
LDADD+=		${LIBKBDDIR}/xmalloc.o
LDADD+=		${LIBKBDDIR}/getfd.o
LDADD+=		${LIBKBDDIR}/mapscrn.o
LDADD+=		${LIBKBDDIR}/loadunimap.o
LDADD+=		${LIBKBDDIR}/kdmapop.o
LDADD+=		${LIBKBDDIR}/kdfontop.o
LDADD+=		${LIBKBDDIR}/psffontop.o
LDADD+=		${LIBKBDDIR}/utf8.o

${MAN}:
	rm -f  ${.TARGET}
	sed -e 's,@datadir@,/usr/share/kbd,' ${DIST}/man/man8/${.TARGET}.in > \
		${.TARGET}

.include <bsd.prog.mk>
