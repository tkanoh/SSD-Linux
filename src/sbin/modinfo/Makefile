#	$ssdlinux: Makefile,v 1.5 2004/06/16 23:04:49 kanoh Exp $

.include <bsd.own.mk>

PROG=		modinfo
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/modutils
.PATH:		${DIST}/insmod ${DIST}/man

.include "${.CURDIR}/../../lib/modutils/Makefile.cflags"

CPPFLAGS+=	-DCOMBINE_rmmod -DCOMBINE_modprobe -DCOMBINE_lsmod
CPPFLAGS+=	-DCOMBINE_ksyms -DCOMBINE_kallsyms	

LDADD+=		-L${LIBMODU}/libobj -lobj
LDADD+=		-L${LIBMODU}/libutil -lutil
LDADD+=		-L${LIBMODU}/../libz -lz
DPADD+=		${LIBMODU}/libobj/libobj.a
DPADD+=		${LIBMODU}/libutil/libutil.a

.include <bsd.prog.mk>
