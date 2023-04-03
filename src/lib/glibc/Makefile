#	$ssdlinux: Makefile,v 1.5 2004/06/17 17:17:38 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=	glibc
HAVE_DESTDIR= 1
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_ENV=
CONFIGURE_OPTIONS=  --enable-add-ons=linuxthreads --without-cvs
.if ${GLIBC_VERSION} != "2.3.1"
CONFIGURE_OPTIONS+=  --build=${MACHTYPE}
.endif
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS= install_root=$(DESTDIR)
INSTALL_STRIP=  no

SYMLINKS+=	/usr/src/linux/include/asm /usr/include/asm
SYMLINKS+=	/usr/src/linux/include/linux /usr/include/linux

GNU_STRIP=      /sbin/ldconfig
GNU_STRIP+=     /sbin/sln

.if defined(CROSS_BUILD) || defined(NEW_GLIBC) 
POSTINSTALL_SCRIPT= \
	(cd ${DESTDIR}/usr/include/rpcsvc && \
		for i in `ls -1 *.x | sed -e 's/\.x//'` ; do \
			if [ ! -f $${i}.h ] ; then \
				rpcgen -h $${i}.x -o $${i}.h; \
			fi; \
		done) 
.endif

.include <bsd.gnu.mk>
