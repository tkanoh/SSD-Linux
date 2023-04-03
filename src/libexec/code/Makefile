#	$ssdlinux: Makefile,v 1.1 2004/10/18 06:04:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		code
MKMAN=		no

DIST=		${.CURDIR}/../../dist/findutils
.PATH:		${DIST}/locate

LDADD+=		${.CURDIR}/../frcode/version.o
.include "${DIST}/../../lib/findutils/Makefile.ldflags"

CPPFLAGS+=	-I${DIST}/locate
.include "${LIBFINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
