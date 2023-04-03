#	$ssdlinux: Makefile,v 1.7 2004/03/23 14:15:15 yamagata Exp $

.include <bsd.own.mk>

PROG=		ls		

.if ${TARGET_HOSTTYPE} == "i386"
SRCS=		ls-50.c
DIST=		${.CURDIR}/../../../dist/coreutils50
LIBCUDIR=	${.CURDIR}/../../../lib/coreutils50
.elif ${TARGET_HOSTTYPE} == "powerpc"
SRCS=		ls.c
DIST=		${.CURDIR}/../../../dist/coreutils
LIBCUDIR=	${.CURDIR}/../../../lib/coreutils
.endif

SRCS+=		ls-ls.c
MKMAN=		no

.PATH:		${DIST}/src

CPPFLAGS+=	-DNO_USAGE
.include "${LIBCUDIR}/Makefile.cflags"
LIBFUDIR=	${.CURDIR}/../libhack
LDADD+=		-L${LIBFUDIR} -lhack
DPADD+=		${LIBFUDIR}/libhack.a
LDADD+=		-lrt

LDSTATIC=	-static -s

proginstall:

.include <bsd.prog.mk>
