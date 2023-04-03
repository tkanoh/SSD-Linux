#	$ssdlinux: Makefile,v 1.5 2003/07/04 04:01:13 yamagata Exp $

.include <bsd.own.mk>

PROG=		test		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

LINKS=		${BINDIR}/test ${BINDIR}/[

.include <bsd.prog.mk>
