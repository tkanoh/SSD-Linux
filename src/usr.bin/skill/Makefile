#	$ssdlinux: Makefile,v 1.5 2004/02/25 04:46:47 yamagata Exp $

.include <bsd.own.mk>

PROG=		skill
MAN=		${PROG}.1 snice.1

DIST=		${.CURDIR}/../../dist/procps
.PATH:		${DIST}

LIBPROCDIR=	${.CURDIR}/../../lib/libproc
LDDIR!=		cd ${LIBPROCDIR} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lproc
DPADD+=		${LIBPROCDIR}/libproc.a

CPPFLAGS+=      -D_GNU_SOURCE -fno-common -ffast-math \
		-W -Wall -Wshadow -Wcast-align -Wredundant-decls \
		-Wbad-function-cast -Wcast-qual -Wwrite-strings \
		-Waggregate-return \
		-Wstrict-prototypes -Wmissing-prototypes
LDFLAGS=	-s

LINKS+=		${BINDIR}/${PROG} ${BINDIR}/snice

NOGCCERROR=	yes

.include <bsd.prog.mk>
