#	$ssdlinux: Makefile,v 1.7 2004/07/04 06:01:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		watch

DIST=		${.CURDIR}/../../dist/procps
.PATH:		${DIST}

LIBNCURSESDIR=	${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=		cd ${LIBNCURSESDIR} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lncurses
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
