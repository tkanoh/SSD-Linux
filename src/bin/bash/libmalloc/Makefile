#	$ssdlinux: Makefile,v 1.3 2002/08/08 00:46:39 yamagata Exp $

.include <bsd.own.mk>

LIB=		malloc
SRCS=		${LIB}.c trace.c stats.c table.c watch.c

DIST=		${.CURDIR}/../../../dist/bash
.PATH:		${DIST}/lib/${LIB}

CPPFLAGS+=	-DRCHECK -Dbotch=programming_error

libinstall::

NOGCCERROR=	yes

.include <bsd.lib.mk>
