#	$ssdlinux: Makefile,v 1.6 2003/07/04 02:24:14 yamagata Exp $

.include <bsd.own.mk>

PROG=		dir		
SRCS=		ls-dir.c

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../../bin/ls/ls.o
.include "${LIBCUDIR}/Makefile.ldflags"
LDADD+=		-lrt

.include <bsd.prog.mk>
