#	$ssdlinux: Makefile,v 1.5 2002/12/26 14:28:36 kanoh Exp $

.include <bsd.own.mk>

PROG=		rdev
MAN=		${PROG}.8 ramsize.8 vidmode.8 rootflags.8

DIST=		${.CURDIR}/../../dist/util-linux
.PATH:		${DIST}/sys-utils

LIBULDIR=	${.CURDIR}/../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${DIST}/lib -I${LIBULDIR}/dummy

.if ${TARGET_HOSTTYPE} == "i386"
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/ramsize
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/vidmode
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/rootflags
.endif

.include <bsd.prog.mk>
