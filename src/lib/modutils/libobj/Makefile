#	$ssdlinux: Makefile,v 1.6 2004/07/13 05:16:10 yamagata Exp $

.include <bsd.own.mk>

LIB=		obj
SRCS=		obj_kallsyms.c obj_common.c obj_load.c obj_reloc.c
.if ${TARGET_HOSTTYPE} == "i386"
SRCS+=		obj_i386.c
.elif ${TARGET_HOSTTYPE} == "powerpc"
SRCS+=		obj_ppc.c
.endif
SRCS+=		obj_gpl_license.c

MKMAN=		no

DIST=		${.CURDIR}/../../../dist/modutils
.PATH:		${DIST}/${LIB}

.include "${.CURDIR}/../Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
