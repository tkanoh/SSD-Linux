#	$ssdlinux: Makefile,v 1.6 2003/07/04 03:34:57 yamagata Exp $

.include <bsd.own.mk>

PROG=		paste

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
