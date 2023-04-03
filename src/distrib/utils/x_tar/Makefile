#	$ssdlinux: Makefile,v 1.4 2004/12/21 07:34:25 yamagata Exp $

.include <bsd.own.mk>

PROG=		tar
SRCS=		buffer.c compare.c create.c delete.c extract.c xheader.c \
		incremen.c list.c mangle.c misc.c names.c sparse.c \
		system.c tar.c update.c utf8.c
SRCS+=		prepargs.c rtapelib.c localcharset.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST}/src ${DIST}/lib

TARSRC=		${.CURDIR}/../../../usr.bin/${PROG}
CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DLIBDIR=\"/usr/lib\"
CPPFLAGS+=	-I${TARSRC}/src
CPPFLAGS+=	-I${DIST}/src
CPPFLAGS+=	-I${TARSRC}/include
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-DNO_USAGE

LIBRTDIR=	${.CURDIR}/../../../lib/glibc/build/rt
LDADD+=		-L${LIBRTDIR} -lrt
DPADD+=		${LIBRTDIR}/librt.a

all: 

install:

.include <bsd.prog.mk>
