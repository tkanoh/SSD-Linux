#	$ssdlinux: Makefile,v 1.7 2003/07/04 02:07:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		rm		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../mv/remove.o
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
