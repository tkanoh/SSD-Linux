#	$ssdlinux: Makefile,v 1.4 2003/07/04 03:43:18 yamagata Exp $

.include <bsd.own.mk>

PROG=		sha1sum

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../md5sum/md5sum.o
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
