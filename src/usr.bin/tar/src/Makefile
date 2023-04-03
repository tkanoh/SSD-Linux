#	$ssdlinux: Makefile,v 1.10 2005/01/06 03:28:10 yamagata Exp $

.include <bsd.own.mk>

PROG=		tar
SRCS=		buffer.c compare.c create.c delete.c extract.c xheader.c \
		incremen.c list.c mangle.c misc.c names.c sparse.c \
		system.c tar.c update.c utf8.c
MKMAN=		no
FILES=		tar.info
FILESDIR=	/usr/share/info

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST}/src ${DIST}/doc

.include "${.CURDIR}/../Makefile.cflags"
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}/src
CPPFLAGS+=	-I${.CURDIR}/../include
CPPFLAGS+=	-I${DIST}/lib

LIBRTDIR=	${.CURDIR}/../../../lib/glibc/build/rt
LDADD+=         -L${.CURDIR}/../lib -ltar
LDADD+=         -L${LIBRTDIR} -lrt
DPADD+=         ${.CURDIR}/../lib/libtar.a
DPADD+=         ${LIBRTDIR}/librt.a

install:
	install-info ${DESTDIR}${FILESDIR}/${PROG}.info ${DESTDIR}${FILESDIR}/dir

.include <bsd.prog.mk>
