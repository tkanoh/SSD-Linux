#	$ssdlinux: Makefile,v 1.3 2004/10/18 05:33:58 yamagata Exp $

.include <bsd.own.mk>

PROG=		find
SRCS=		${PROG}.c fstype.c parser.c pred.c tree.c util.c version.c

DIST=		${.CURDIR}/../../dist/findutils
.PATH:		${DIST}/${PROG}

.include "${DIST}/../../lib/findutils/Makefile.ldflags"

CPPFLAGS+=	-I${DIST}/${PROG}
.include "${LIBFINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
