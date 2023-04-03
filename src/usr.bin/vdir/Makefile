#	$ssdlinux: Makefile,v 1.5 2003/07/04 02:25:22 yamagata Exp $

.include <bsd.own.mk>

PROG=		vdir		
SRCS=		ls-vdir.c

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../../bin/ls/ls.o
.include "${LIBCUDIR}/Makefile.ldflags"
LDADD+=		-lrt


.include <bsd.prog.mk>
