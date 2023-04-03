#	$ssdlinux: Makefile,v 1.7 2003/07/04 02:06:09 yamagata Exp $

.include <bsd.own.mk>

PROG=		mv		
SRCS=		${PROG}.c remove.c

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../cp/copy.o \
		${.CURDIR}/../cp/cp-hash.o
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
