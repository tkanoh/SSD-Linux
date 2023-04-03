#	$ssdlinux: Makefile,v 1.6 2004/12/07 09:18:50 todoroki Exp $

.include <bsd.own.mk>

PROG=		cal

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/misc-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DESTDIR}/usr/include
.endif
LDADD+=		${LIBULDIR}/err.o
LIBNCURSES=	${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=		cd ${LIBNCURSES} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lncurses
DPADD+=		${LIBNCURSES}/libncurses.a

.include <bsd.prog.mk>
