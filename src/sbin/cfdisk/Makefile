#	$ssdlinux: Makefile,v 1.9 2004/11/05 03:26:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		cfdisk
SRCS=		${PROG}.c llseek.c disksize.c i386_sys_types.c
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/fdisk

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DESTDIR}/usr/include
.endif
LDADD+=		${LIBULDIR}/xstrncpy.o
LIBNCURSES=	${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=		cd ${LIBNCURSES} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lncurses
DPADD+=		${LIBNCURSES}/libncurses.a

NOGCCERROR=	yes

.include <bsd.prog.mk>
