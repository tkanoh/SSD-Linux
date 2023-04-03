#	$ssdlinux: Makefile,v 1.3 2003/07/04 02:49:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		powerpc-ssd-linux-gnu-install
SRCS=		install.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/coreutils
.PATH:		${DIST}/src

LIBCUDIR=	${.CURDIR}/../../../lib/coreutils
CPPFLAGS+=	-DSTRIPBINPATH=\"powerpc-ssd-linux-gnu-strip\"
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../../../bin/cp/copy.o \
		${.CURDIR}/../../../bin/cp/cp-hash.o
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
