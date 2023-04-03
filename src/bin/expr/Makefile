#	$ssdlinux: Makefile,v 1.7 2003/07/04 03:54:41 yamagata Exp $

.include <bsd.own.mk>

PROG=		expr		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
