#	$ssdlinux: Makefile,v 1.11 2004/06/12 14:51:35 kanoh Exp $
TOOLCHAIN= yes

.include <bsd.own.mk>

DISTNAME=	gcc
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_ENV=	CFLAGS="-O2" CXXFLAGS="-O2" LDFLAGS=-s
CONFIGURE_OPTIONS=  --with-gnu-ld --enable-threads --verbose
CONFIGURE_OPTIONS+= --enable-languages=c,c++
GMAKE_ENV=
GMAKE_OPTIONS= LANGUAGES="c c++"
GMAKE_INSTALL_OPTIONS=
INSTALL_STRIP=	no

GNU_TARGET=	${TARGET_MACHTYPE}${NEW_GLIBC}
GNU_WITH_HEADER=${TOOLCHAINDIR}/include
GNU_WITH_LIBS=${TOOLCHAINDIR}/lib
CONFIGURE_OPTIONS+= --with-gxx-include-dir=${GNU_WITH_HEADER}/c++/${GCC_VERSION}

.include <bsd.gnu.mk>
