#	$ssdlinux: Makefile,v 1.5 2002/12/12 09:09:54 yamagata Exp $
#	$NetBSD: Makefile,v 1.7 2001/12/12 01:48:52 tv Exp $

.include <bsd.own.mk>

LIB=		common
SRCS=		${LIB}.c displayq.c getcap.c rmjob.c startdaemon.c

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

.PATH:		${DIST}/common_source

libinstall:

.include <bsd.lib.mk>
