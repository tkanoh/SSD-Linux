#	$ssdlinux: Makefile,v 1.3 2004/04/27 09:32:52 yamagata Exp $

.include 	<bsd.own.mk>

LIB=		rsync
SRCS=		wildmatch.c compat.c snprintf.c mdfour.c permstring.c pool_alloc.c

DIST=		${.CURDIR}/../../../dist/rsync
.PATH:		${DIST}/lib

CPPFLAGS+=	-I${.CURDIR}/../ -I${DIST}

libinstall::

.include <bsd.lib.mk>
