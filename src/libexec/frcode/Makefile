#	$ssdlinux: Makefile,v 1.1 2004/10/18 06:04:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		frcode
SRCS=		frcode.c version.c
MKMAN=		no

DIST=		${.CURDIR}/../../dist/findutils
.PATH:		${DIST}/locate ${DIST}/find

.include "${DIST}/../../lib/findutils/Makefile.ldflags"

CPPFLAGS+=	-I${DIST}/locate
.include "${LIBFINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
