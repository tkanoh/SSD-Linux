#	$ssdlinux: Makefile,v 1.7 2004/06/16 23:04:49 kanoh Exp $

.include <bsd.own.mk>

PROG=		insmod
SRCS=		${PROG}.c rmmod.c modprobe.c lsmod.c ksyms.c kallsyms.c
SCRIPTS=	insmod_ksymoops_clean kernelversion
MAN=		${PROG}.8 modules.conf.5
MAN+=		rmmod.8 modprobe.8 lsmod.8 ksyms.8 kallsyms.8

# force shared
LDSTATIC=

DIST=		${.CURDIR}/../../dist/modutils
.PATH:		${DIST}/${PROG} ${DIST}/man

.include "${.CURDIR}/../../lib/modutils/Makefile.cflags"

CPPFLAGS+=	-DTAINT_URL='"http://www.tux.org/lkml/\#export-tainted"'
CPPFLAGS+=	-DCOMBINE_rmmod -DCOMBINE_modprobe -DCOMBINE_lsmod
CPPFLAGS+=	-DCOMBINE_ksyms -DCOMBINE_kallsyms	

LDADD+=		-L${LIBMODU}/libobj -lobj
LDADD+=		-L${LIBMODU}/libutil -lutil
LDADD+=		-L${LIBMODU}/../libz -lz
DPADD+=		${LIBMODU}/libobj/libobj.a
DPADD+=		${LIBMODU}/libutil/libutil.a

SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/rmmod
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/modprobe
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/lsmod
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/ksyms
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/kallsyms

.include <bsd.prog.mk>
