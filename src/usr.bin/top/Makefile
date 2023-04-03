#	$ssdlinux: Makefile,v 1.9 2004/07/04 06:00:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		top

DIST=		${.CURDIR}/../../dist/procps
.PATH:		${DIST}

LIBPROCDIR=	${.CURDIR}/../../lib/libproc
LDADD+=		-L${LIBPROCDIR} -lproc
DPADD+=		${LIBPROCDIR}/libproc.a

LIBNCURSESDIR=	${.CURDIR}/../../lib/libncurses/build/lib
LDADD+=		-L${LIBNCURSESDIR} -lncurses
DPADD+=		${LIBNCURSESDIR}/libncurses.a

CPPFLAGS+=	-D_GNU_SOURCE -fno-common -ffast-math \
		-W -Wall -Wshadow -Wcast-align -Wredundant-decls \
		-Wbad-function-cast -Wcast-qual -Wwrite-strings \
		-Waggregate-return \
		-Wstrict-prototypes -Wmissing-prototypes
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${DIST}/../ncurses/include
.endif
LDFLAGS=	-s

NOGCCERROR=	yes

.include <bsd.prog.mk>
