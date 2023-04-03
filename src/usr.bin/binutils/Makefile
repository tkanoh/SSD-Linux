#	$ssdlinux: Makefile,v 1.3 2003/02/12 04:56:51 yamagata Exp $

.include <bsd.own.mk>

DISTNAME=		binutils
HAVE_DESTDIR=		1
CONFIGURE_FULL_PREFIX=	1
CONFIGURE_ENV=		CFLAGS="-Wall -O2" CXXFLAGS="-Wall -O2" LDFLAGS=-s
CONFIGURE_OPTIONS=	--enable-shared --with-gnu-ld --enable-threads --verbose
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS=	DESTDIR=${DESTDIR}
INSTALL_STRIP=		no

.include <bsd.gnu.mk>
