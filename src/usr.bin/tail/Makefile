#	$ssdlinux: Makefile,v 1.6 2003/07/04 03:46:53 yamagata Exp $

.include <bsd.own.mk>

PROG=		tail

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"
LDADD+=		-lm -lrt


.include <bsd.prog.mk>
