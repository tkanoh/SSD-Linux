#	$ssdlinux: Makefile,v 1.5 2004/07/04 06:08:30 yamagata Exp $

.include <bsd.own.mk>

PROG=		setterm

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/misc-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DESTDIR}/usr/include
.endif
LIBNCURSES=	${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=         cd ${LIBNCURSES} && ${PRINTOBJDIR}
LDADD+=         -L${LDDIR} -lncurses
DPADD+=         ${LIBNCURSES}/libncurses.a

.include <bsd.prog.mk>
