#	$ssdlinux: Makefile,v 1.4 2002/11/08 07:17:24 yamagata Exp $

.include <bsd.own.mk>

PROG=		loadkeys
MAN=		${PROG}.1 keymaps.5
CLEANFILES=	${PROG}.c ${PROG}.1

YACC=		bison
YFLAGS=		-y

DIST=		${.CURDIR}/../../dist/kbd
.PATH:		${DIST}/src ${DIST}/man/man5

LIBKBDDIR=	${.CURDIR}/../../lib/kbd

CPPFLAGS+=	-DDATADIR=\"/usr/share/kbd\" 
CPPFLAGS+=	-I${LIBKBDDIR} -I${LIBKBDDIR}/dummy -I${DIST}/src
LDADD=    	${LIBKBDDIR}/ksyms.o
LDADD+=    	${LIBKBDDIR}/xmalloc.o
LDADD+=    	${LIBKBDDIR}/findfile.o
LDADD+=    	${LIBKBDDIR}/getfd.o

${PROG}.1:
	rm -f  ${.TARGET}
	sed -e 's,@datadir@,/usr/share/kbd,' ${DIST}/man/man1/${.TARGET}.in > \
		${.TARGET}

.include <bsd.prog.mk>
