#	$ssdlinux: Makefile,v 1.5 2002/12/27 06:10:31 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=	glibc
HAVE_DESTDIR= 1
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_ENV=
CONFIGURE_OPTIONS=  --enable-add-ons=linuxthreads --without-cvs
CONFIGURE_OPTIONS+= --enable-static-nss
CONFIGURE_OPTIONS+= --disable-shared
.if ${TARGET_HOSTTYPE} == "powerpc"
CONFIGURE_OPTIONS+= --enable-versioning
.endif
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS= install_root=$(DESTDIR)
INSTALL_STRIP=  no

SYMLINKS+=	/usr/src/linux/include/asm /usr/include/asm
SYMLINKS+=	/usr/src/linux/include/linux /usr/include/linux

NO_INSTALL=	yes

.include <bsd.gnu.mk>
