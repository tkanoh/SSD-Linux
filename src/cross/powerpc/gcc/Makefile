#	$ssdlinux: Makefile,v 1.10 2004/01/22 02:51:38 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=	gcc
HAVE_DESTDIR=	1
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_ENV=	CFLAGS="-O2" CXXFLAGS="-O2" LDFLAGS=-s
CONFIGURE_OPTIONS=  --with-gnu-ld --enable-threads --verbose 
CONFIGURE_OPTIONS+= --enable-languages=c,c++
GMAKE_ENV=
GMAKE_OPTIONS= LANGUAGES="c c++"
GMAKE_INSTALL_OPTIONS= DESTDIR=${DESTDIR}
INSTALL_STRIP=	no

GNU_TARGET=	powerpc-ssd-linux-gnu
GNU_WITH_HEADER=/usr/cross/powerpc/${GNU_TARGET}/include
CONFIGURE_OPTIONS+= --with-gxx-include-dir=${GNU_WITH_HEADER}/c++/${GCC_VERSION}

.include <bsd.gnu.mk>
