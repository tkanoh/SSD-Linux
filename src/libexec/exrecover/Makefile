#	$ssdlinux: Makefile,v 1.1 2002/12/12 03:54:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		exrecover
SRCS=		${PROG}.c mapmalloc.c
MKMAN=		no

DIST=		${.CURDIR}/../../dist/ex
.PATH:		${DIST}

.include "${.CURDIR}/../../usr.bin/ex/Makefile.cflags"

.include <bsd.prog.mk>
