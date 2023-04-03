#	$ssdlinux: Makefile,v 1.10 2004/11/10 07:07:33 yamagata Exp $

.include <bsd.own.mk>

DISTNAME=		gdb
CONFIGURE_FULL_PREFIX=	1
CONFIGURE_ENV=		CFLAGS="-O2" CXXFLAGS="-O2"
CONFIGURE_OPTIONS=	--with-gnu-ld
GMAKE_ENV=
GMAKE_OPTIONS=
INSTALL_STRIP=		no

GNU_STRIP=		${BINDIR}/${DISTNAME}

.include <bsd.gnu.mk>
