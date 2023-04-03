#	$ssdlinux: Makefile,v 1.11 2004/06/17 17:09:54 kanoh Exp $

CROSS_BUILD=	powerpc
CROSS_LIB=	yes

.include <bsd.own.mk>

DISTNAME=	glibc
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_OPTIONS=  --enable-add-ons=linuxthreads --without-cvs
.if ${GLIBC_VERSION} != "2.3.1"
CONFIGURE_OPTIONS+=  --build=${MACHTYPE}
.endif

_TARGET_DIR=	/usr/cross/${CROSS_BUILD}/${TARGET_MACHTYPE}
.ifdef HAVE_SYSINCLUDE 
GNU_WITH_HEADER=${_TARGET_DIR}/sys-include
.else
GNU_WITH_HEADER=${_TARGET_DIR}/include
.endif

HAVE_DESTDIR= 1
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS= install_root=$(DESTDIR)
INSTALL_STRIP=  no

POSTINSTALL_SCRIPT= \
	(cd ${DESTDIR}/${_TARGET_DIR}/include/rpcsvc && \
		for i in `ls -1 *.x | sed -e 's/\.x//'` ; do \
			if [ ! -f $${i}.h ] ; then \
				rpcgen -h $${i}.x -o $${i}.h; \
			fi; \
		done) 

.include <bsd.gnu.mk>
