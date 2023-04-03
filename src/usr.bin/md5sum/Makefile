#	$ssdlinux: Makefile,v 1.6 2003/07/04 03:32:20 yamagata Exp $

.include <bsd.own.mk>

PROG=		md5sum
SRCS=		${PROG} md5.c

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
