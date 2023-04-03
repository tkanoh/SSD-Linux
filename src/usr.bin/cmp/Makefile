#	$ssdlinux: Makefile,v 1.3 2002/10/01 03:04:38 yamagata Exp $

.include <bsd.own.mk>

PROG=		cmp
SRCS=		${PROG}.c version.c \
		c-stack.c cmpbuf.c error.c exitfail.c freesoft.c \
		getopt.c getopt1.c hard-locale.c offtostr.c \
		xmalloc.c xstrtoumax.c

DIST=		${.CURDIR}/../../dist/diffutils
.PATH:		${DIST}/lib ${DIST}/src ${DIST}/man

CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-DHAVE_CONFIG_H -DNULL_DEVICE=\"/dev/null\"
CPPFLAGS+=	-I${.CURDIR} -I${DIST}/lib

.include <bsd.prog.mk>
