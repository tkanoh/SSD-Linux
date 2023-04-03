#	$ssdlinux: Makefile,v 1.4 2004/10/18 05:34:19 yamagata Exp $

.include <bsd.own.mk>

PROG=		xargs

DIST=		${.CURDIR}/../../dist/findutils
.PATH:		${DIST}/${PROG}

LDADD+=		${.CURDIR}/../find/version.o
.include "${DIST}/../../lib/findutils/Makefile.ldflags"

CPPFLAGS+=	-I${DIST}/${PROG}
.include "${LIBFINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
