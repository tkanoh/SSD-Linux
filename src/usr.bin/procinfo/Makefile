#	$ssdlinux: Makefile,v 1.5 2004/07/04 05:53:38 yamagata Exp $

.include <bsd.own.mk>

PROG=		procinfo
SCRIPTS=	lsdev socklist
CLEANFILES=	${SCRIPTS}
MAN=		${PROG}.8 lsdev.8
SRCS=		procinfo.c routines.c

DIST=		${.CURDIR}/../../dist/procinfo
.PATH:		${DIST}

LIBNCURSESDIR=	${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=		cd ${LIBNCURSESDIR} && ${PRINTOBJDIR}
LDADD+=		-L${LDDIR} -lncurses
DPADD+=		${LIBNCURSESDIR}/libncurses.a

CPPFLAGS+=	-I${DIST}
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${DIST}/../ncurses/include
.endif

LDFLAGS=	-s

lsdev: lsdev.pl
	cp ${DIST}/lsdev.pl lsdev

socklist: socklist.pl
	cp ${DIST}/socklist.pl socklist

.include <bsd.prog.mk>
