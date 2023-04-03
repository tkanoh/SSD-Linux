#	$ssdlinux: Makefile,v 1.3 2003/01/07 03:31:39 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=	groff
NO_GNU_TARGET= 1
NO_GNU_HOST= 1
CONFIGURE_ENV= CXXFLAGS=-Dstrerror=strerror
CONFIGURE_FULL_PREFIX= 1
.if defined(CROSS_BUILD)
CONFIGURE_OPTIONS= --host=${TARGET_MACHTYPE}
.else
CONFIGURE_OPTIONS=
.endif
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS= manroot=${DESTDIR}${MANDIR}
INSTALL_STRIP=	no

.include <bsd.gnu.mk>
