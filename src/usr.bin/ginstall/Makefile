#	$ssdlinux: Makefile,v 1.6 2003/07/04 02:22:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		ginstall		
SRCS=		install.c
MAN=		install.1

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
LDADD=		${.CURDIR}/../../bin/cp/copy.o \
		${.CURDIR}/../../bin/cp/cp-hash.o
.include "${LIBCUDIR}/Makefile.ldflags"

SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/install
SYMLINKS+=	${MANDIR}/man1/${MAN} ${MANDIR}/man1/${PROG}.1

.include <bsd.prog.mk>
