#	$ssdlinux: Makefile,v 1.4 2002/11/27 03:48:02 yamagata Exp $

.include <bsd.own.mk>

PROG=		hexdump
SRCS=		${PROG}.c conv.c display.c hexsyntax.c odsyntax.c parse.c

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/text-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.include <bsd.prog.mk>
