#	$ssdlinux: Makefile,v 1.4 2004/11/05 07:22:46 yamagata Exp $

.include <bsd.own.mk>

PROG=		slabtop

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
CPPFLAGS+=	-I${DESTDIR}/usr/include
NOGCCERROR=	yes
.endif
LDFLAGS=	-s

.include <bsd.prog.mk>
