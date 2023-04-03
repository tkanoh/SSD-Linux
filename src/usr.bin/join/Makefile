#	$ssdlinux: Makefile,v 1.7 2003/07/04 03:31:21 yamagata Exp $

.include <bsd.own.mk>

PROG=		join

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
