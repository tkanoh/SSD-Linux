#	$ssdlinux: Makefile,v 1.1 2004/02/23 13:21:00 yamagata Exp $

.include <bsd.own.mk>

PROG=		nohup		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
