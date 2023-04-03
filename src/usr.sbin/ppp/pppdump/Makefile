#	$ssdlinux: Makefile,v 1.1 2002/06/21 08:47:41 kanoh Exp $

.include <bsd.own.mk>

PROG=		pppdump
SRCS=		${PROG}.c bsd-comp.c deflate.c zlib.c
MAN=		${PROG}.8

CPPFLAGS+=	-I${DIST}/include/net

.include <bsd.prog.mk>
