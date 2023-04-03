#	$ssdlinux: Makefile,v 1.7 2003/02/09 22:15:07 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=	gcc
HAVE_DESTDIR=	1
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_ENV=	CFLAGS="-O2" CXXFLAGS="-O2" LDFLAGS=-s
CONFIGURE_OPTIONS= --enable-threads --verbose
CONFIGURE_OPTIONS+= --enable-languages=c --with-newlib
GMAKE_ENV=
GMAKE_OPTIONS= LANGUAGES=c all-gcc
GMAKE_INSTALL_OPTIONS= DESTDIR=${DESTDIR}
INSTALL_STRIP=	no

GNU_TARGET=	powerpc-ssd-linux-gnu
GNU_WITH_HEADER=/usr/src/dist/ppc-headers/include
GNU_WITH_LIBS=	/usr/src/dist/ppc-headers/lib

.include <bsd.gnu.mk>
