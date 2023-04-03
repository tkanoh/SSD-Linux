#	$ssdlinux: Makefile,v 1.6 2003/07/04 02:29:41 yamagata Exp $

.include <bsd.own.mk>

PROG=		chown		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../../usr.bin/chgrp/chown-core.o
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
