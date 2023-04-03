#	$ssdlinux: Makefile,v 1.4 2003/12/04 10:19:31 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=		binutils
HAVE_DESTDIR=		1
CONFIGURE_FULL_PREFIX=	1
CONFIGURE_ENV=		CFLAGS="-Wall -O2" CXXFLAGS="-Wall -O2" LDFLAGS=-s
CONFIGURE_OPTIONS=	--enable-threads --verbose
GNU_TARGET=		powerpc-ssd-linux-gnu
.ifdef HAVE_INCLUDE
GNU_WITH_HEADER=	/usr/cross/powerpc/${GNU_TARGET}/include
.else
GNU_WITH_HEADER=	/usr/src/dist/ppc-headers/include
.endif
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS=	DESTDIR=${DESTDIR}
INSTALL_STRIP=		no


.include <bsd.gnu.mk>
