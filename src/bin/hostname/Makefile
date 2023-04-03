#	$ssdlinux: Makefile,v 1.5 2003/07/04 03:55:28 yamagata Exp $

.include <bsd.own.mk>

PROG=		hostname		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
