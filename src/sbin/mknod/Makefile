#	$ssdlinux: Makefile,v 1.5 2003/07/04 02:11:08 yamagata Exp $

.include 	<bsd.own.mk>

PROG=		mknod		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
