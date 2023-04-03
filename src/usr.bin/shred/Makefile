#	$ssdlinux: Makefile,v 1.5 2003/07/04 02:27:52 yamagata Exp $

.include <bsd.own.mk>

PROG=		shred		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"
LDADD+=		-lrt

.include <bsd.prog.mk>
