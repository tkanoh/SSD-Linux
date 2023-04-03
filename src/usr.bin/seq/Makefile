#	$ssdlinux: Makefile,v 1.5 2003/07/04 04:20:32 yamagata Exp $

.include <bsd.own.mk>

PROG=		seq		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"
LDADD+=		-lm

.include <bsd.prog.mk>
