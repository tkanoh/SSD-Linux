#	$ssdlinux: Makefile,v 1.2 2004/11/08 04:03:53 yamagata Exp $

.include <bsd.own.mk>

PROG=		cmp
SRCS=		${PROG}.c version.c \
		c-stack.c cmpbuf.c error.c exitfail.c freesoft.c \
		getopt.c getopt1.c offtostr.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/diffutils
.PATH:		${DIST}/lib ${DIST}/src

CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-DHAVE_CONFIG_H -DNULL_DEVICE=\"/dev/null\"
CPPFLAGS+=	-DNO_USAGE
CPPFLAGS+=	-I${DIST}/src
CPPFLAGS+=	-I${.CURDIR}/../../../usr.bin/${PROG}
CPPFLAGS+=	-I${DIST}/lib

proginstall:

.include <bsd.prog.mk>
