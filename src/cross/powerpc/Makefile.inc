#	$ssdlinux: Makefile.inc,v 1.4 2003/12/04 10:19:31 kanoh Exp $

WARNS?=		0
WFORMAT?=	2
NONLS=		yes
GNU_PREFIX=	/usr/cross/powerpc
_TARGET=	powerpc-ssd-linux-gnu
BINDIR=		${GNU_PREFIX}/bin
INCSDIR=	${GNU_PREFIX}/${_TARGET}/include
GNU_BINDIR=	${BINDIR}
GNU_INCLUDEDIR=	${INCSDIR}
GNU_SBINDIR=	${GNU_PREFIX}/sbin
GNU_INFODIR=	${GNU_PREFIX}/share/info
GNU_MANDIR=	${GNU_PREFIX}/share/man
.ifdef CROSS_LIB
GNU_EXEC_PREFIX=${GNU_PREFIX}/${_TARGET}
LIBDIR=		${GNU_EXEC_PREFIX}/lib
.else
LIBDIR=		${GNU_PREFIX}/lib
.endif
GNU_LIBDIR=	${LIBDIR}

DISTDIR=	../../../../dist/${DISTNAME}
