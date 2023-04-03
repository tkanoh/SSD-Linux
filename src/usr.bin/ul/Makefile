#	$ssdlinux: Makefile,v 1.6 2004/07/04 06:11:15 yamagata Exp $

.include <bsd.own.mk>

PROG=		ul

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/text-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${DIST}/../ncurses/include
.endif
LIBNCURSES=	${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=		cd ${LIBNCURSES} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lncurses
DPADD+=		${LIBNCURSES}/libncurses.a

.include <bsd.prog.mk>
