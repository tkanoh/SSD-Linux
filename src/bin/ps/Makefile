#	$ssdlinux: Makefile,v 1.8 2004/02/25 04:44:36 yamagata Exp $

.include <bsd.own.mk>

PROG=		ps
SRCS=		display.c global.c help.c output.c parser.c select.c sortformat.c

DIST=		${.CURDIR}/../../dist/procps
.PATH:		${DIST}/${PROG}

LIBPROCDIR=	${.CURDIR}/../../lib/libproc
LDDIR!=		cd ${LIBPROCDIR} && ${PRINTOBJDIR}
.if ${FULL_SHARED} == "yes"
LDADD+=		-L${LDDIR} -lproc
.else
LDADD+=		${LIBPROCDIR}/libproc.a
LDSTATIC=
.endif
DPADD+=		${LIBPROCDIR}/libproc.a

CPPFLAGS+=	-D_GNU_SOURCE -fno-common -ffast-math \
		-W -Wall -Wshadow -Wcast-align -Wredundant-decls \
		-Wbad-function-cast -Wcast-qual -Wwrite-strings \
		-Waggregate-return \
		-Wstrict-prototypes -Wmissing-prototypes

NOGCCERROR=	yes

.include <bsd.prog.mk>
