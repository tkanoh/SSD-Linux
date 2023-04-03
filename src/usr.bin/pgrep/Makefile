#	$ssdlinux: Makefile,v 1.5 2004/02/25 04:46:25 yamagata Exp $

.include <bsd.own.mk>

PROG=		pgrep

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

LINKS+=		${BINDIR}/${PROG} ${BINDIR}/pkill

NOGCCERROR=	yes

.include <bsd.prog.mk>
