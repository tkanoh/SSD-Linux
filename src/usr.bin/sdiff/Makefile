#	$ssdlinux: Makefile,v 1.4 2002/10/01 03:30:22 yamagata Exp $

.include <bsd.own.mk>

PROG=		sdiff

DIST=		${.CURDIR}/../../dist/diffutils
.PATH:		${DIST}/lib ${DIST}/src ${DIST}/man

CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-DHAVE_CONFIG_H -DDIFF_PROGRAM=\"/usr/bin/diff\"
CPPFLAGS+=	-I${.CURDIR}/../cmp -I${DIST}/lib
LDADD+=		${.CURDIR}/../cmp/version.o \
		${.CURDIR}/../diff/basename.o \
		${.CURDIR}/../cmp/c-stack.o \
		${.CURDIR}/../cmp/exitfail.o \
		${.CURDIR}/../cmp/freesoft.o \
		${.CURDIR}/../cmp/getopt.o \
		${.CURDIR}/../cmp/getopt1.o \
		${.CURDIR}/../cmp/xmalloc.o

.include <bsd.prog.mk>
