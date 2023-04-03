#	$ssdlinux: Makefile,v 1.7 2005/03/18 02:26:18 yamagata Exp $

.include <bsd.own.mk>

PROG=		locate
MAN=		${PROG}.1 updatedb.1 locatedb.5
SCRIPTS=	updatedb
CLEANFILES=	${SCRIPTS}

DIST=		${.CURDIR}/../../dist/findutils
.PATH:		${DIST}/${PROG}

LDADD+=		${.CURDIR}/../find/version.o
.include "${DIST}/../../lib/findutils/Makefile.ldflags"

CPPFLAGS+=	-I${DIST}/${PROG}
.include "${LIBFINDDIR}/Makefile.cflags"

${SCRIPTS}:
	sed \
	-e 's,@bindir@,/usr/bin,' \
	-e 's,@libexecdir@,/usr/libexec,' \
	-e 's,@LOCATE_DB@,/var/db/locatedb,' \
	-e 's,@VERSION@,4.2.20,' \
	-e 's,@find@,find,' \
	-e 's,@frcode@,frcode,' \
	-e 's,@bigram@,bigram,' \
	-e 's,@code@,code,' \
	-e 's,@SORT@,/usr/bin/sort,' \
	-e 's,@SORT_SUPPORTS_Z@,true,' \
	${DIST}/${PROG}/${.TARGET}.sh > ${.TARGET}

NOGCCERROR=	yes
	
.include <bsd.prog.mk>
