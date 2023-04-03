#	$ssdlinux: Makefile,v 1.4 2002/10/09 03:46:01 yamagata Exp $

.include <bsd.own.mk>

PROG=		insmod
SRCS=		insmod.c modprobe.c
#SRCS+=		rmmod.c lsmod.c ksyms.c kallsyms.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/modutils
.PATH:		${DIST}/${PROG} ${DIST}/man

.include "${.CURDIR}/../../../lib/modutils/Makefile.cflags"

CPPFLAGS+=	-DTAINT_URL='"http://www.tux.org/lkml/\#export-tainted"'
CPPFLAGS+=	-DCOMBINE_modprobe
#CPPFLAGS+=	-DCOMBINE_rmmod -DCOMBINE_lsmod
#CPPFLAGS+=	-DCOMBINE_ksyms -DCOMBINE_kallsyms	
CPPFLAGS+=	-DNO_USAGE

LDADD+=		-L${LIBMODU}/libobj -lobj
LDADD+=		-L${LIBMODU}/libutil -lutil
LDADD+=		-lz
DPADD+=		${LIBMODU}/libobj/libobj.a
DPADD+=		${LIBMODU}/libutil/libutil.a

proginstall:

.include <bsd.prog.mk>
