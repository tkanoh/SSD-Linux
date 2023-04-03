#	$ssdlinux: Makefile,v 1.3 2003/12/09 16:48:06 kanoh Exp $

.include <bsd.own.mk>

LIB=		diff
SRCS=		diff.c diff3.c analyze.c cmpbuf.c io.c context.c \
		ed.c normal.c ifdef.c util.c dir.c version.c side.c

DIST=		${.CURDIR}/../../../dist/cvs
.PATH:		${DIST}/diff

CPPFLAGS+=	-I${DIST}/diff \
		-I${.CURDIR}/../ \
		-I${DIST} \
		-I${DIST}/src \
		-I${DIST}/lib
CPPFLAGS+=	-DHAVE_CONFIG_H
.if ${IPV6} == "yes"
CPPFLAGS+=	-DENABLE_IPV6=1
.endif

libinstall::

.include <bsd.lib.mk>
