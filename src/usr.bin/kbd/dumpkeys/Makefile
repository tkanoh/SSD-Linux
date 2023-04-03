#	$ssdlinux: Makefile,v 1.3 2002/11/08 07:23:50 yamagata Exp $

.include <bsd.own.mk>

PROG=		dumpkeys
CLEANFILES=	${PROG}.1

DIST=		${.CURDIR}/../../../dist/kbd
.PATH:		${DIST}/src

LIBKBDDIR=	${.CURDIR}/../../../lib/kbd

CPPFLAGS+=	-Wall -Wmissing-prototypes -Wstrict-prototypes
CPPFLAGS+=	-DDATADIR=\"/usr/share/kbd\" 
CPPFLAGS+=	-I${LIBKBDDIR} -I${LIBKBDDIR}/dummy
LDADD=		${LIBKBDDIR}/ksyms.o
LDADD+=		${LIBKBDDIR}/xmalloc.o
LDADD+=		${LIBKBDDIR}/getfd.o

${PROG}.1:
	rm -f  ${.TARGET}
	sed -e 's,@datadir@,/usr/share/kbd,' ${DIST}/man/man1/${.TARGET}.in > \
		${.TARGET}

.include <bsd.prog.mk>
