#	$ssdlinux: Makefile,v 1.2 2004/11/05 06:41:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		pwdx

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

.include <bsd.prog.mk>
