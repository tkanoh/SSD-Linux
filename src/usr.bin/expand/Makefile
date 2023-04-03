#	$ssdlinux: Makefile,v 1.6 2003/07/04 03:26:16 yamagata Exp $

.include <bsd.own.mk>

PROG=		expand

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
