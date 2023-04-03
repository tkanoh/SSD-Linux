#	$ssdlinux: Makefile,v 1.3 2002/08/08 00:46:39 yamagata Exp $

.include <bsd.own.mk>

LIB=		glob
SRCS=		${LIB}.c strmatch.c smatch.c xmbsrtowcs.c

DIST=		${.CURDIR}/../../../dist/bash
.PATH:		${DIST}/lib/${LIB}

libinstall::

.include <bsd.lib.mk>
