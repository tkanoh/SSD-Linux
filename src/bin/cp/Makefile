#	$ssdlinux: Makefile,v 1.5 2003/07/04 01:58:31 yamagata Exp $

.include <bsd.own.mk>

PROG=		cp		
SRCS=		${PROG}.c copy.c cp-hash.c

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
