#	$ssdlinux: Makefile,v 1.7 2004/06/12 15:42:19 kanoh Exp $

.include <bsd.own.mk>

PROG=		ln		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
