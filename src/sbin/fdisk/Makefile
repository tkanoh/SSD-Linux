#	$ssdlinux: Makefile,v 1.7 2004/11/05 03:27:23 yamagata Exp $

.include <bsd.own.mk>

PROG=		fdisk
SRCS=		${PROG}.c fdiskbsdlabel.c fdisksgilabel.c \
		fdisksunlabel.c fdiskaixlabel.c partname.c
		
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/${PROG}

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy
LDADD+=		${.CURDIR}/../cfdisk/llseek.o
LDADD+=		${.CURDIR}/../cfdisk/disksize.o
LDADD+=		${.CURDIR}/../cfdisk/i386_sys_types.o

.include <bsd.prog.mk>
