#	$ssdlinux: Makefile,v 1.4 2003/01/31 01:41:47 yamagata Exp $

.include <bsd.own.mk>

PROG=		getopt
FILES=		${PROG}-parse.bash ${PROG}-parse.tcsh ${PROG}-test.bash \
		${PROG}-test.tcsh
FILESDIR=	/usr/share/misc/${PROG}
FILESMODE=	555

DIST=		${.CURDIR}/../../dist/util-linux
.PATH: ${DIST}/getopt

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${LIBULDIR}/dummy
CPPFLAGS+=	-I${DIST}/lib

.include <bsd.prog.mk>
