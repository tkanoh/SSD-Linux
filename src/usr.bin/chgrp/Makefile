#	$ssdlinux: Makefile,v 1.4 2003/07/04 02:12:49 yamagata Exp $

.include <bsd.own.mk>

PROG=		chgrp		
SRCS=		${PROG}.c chown-core.c

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
