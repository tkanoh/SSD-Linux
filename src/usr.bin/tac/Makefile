#	$ssdlinux: Makefile,v 1.6 2003/07/04 03:45:58 yamagata Exp $

.include <bsd.own.mk>

PROG=		tac

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
