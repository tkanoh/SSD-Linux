#	$ssdlinux: Makefile,v 1.4 2003/02/13 01:59:01 yamagata Exp $

.include <bsd.own.mk>

DISTNAME=		gdb
CONFIGURE_FULL_PREFIX=	1
CONFIGURE_ENV=		CFLAGS="-O2" CXXFLAGS="-O2"
GMAKE_ENV=
GMAKE_OPTIONS=
INSTALL_STRIP=		no

GNU_TARGET=		powerpc-ssd-linux-gnu
GNU_STRIP=		${BINDIR}/${GNU_TARGET}-${DISTNAME}

.include <bsd.gnu.mk>
