#	$ssdlinux: Makefile,v 1.6 2003/07/04 03:25:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		cut

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
