#	$ssdlinux: Makefile,v 1.8 2004/06/30 02:32:57 kanoh Exp $
TOOLS_GLIBC= yes

.include <bsd.own.mk>

DISTNAME=	glibc
HAVE_DESTDIR= 1
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_OPTIONS=  --enable-add-ons=linuxthreads --without-cvs
GNU_WITH_HEADER=${TOOLCHAINDIR}/${TARGET_MACHTYPE}${NEW_GLIBC}/sys-include

GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS=
INSTALL_STRIP=  no

POSTINSTALL_SCRIPT= \
	(cd ${GNU_WITH_HEADER}/rpcsvc && \
		for i in `ls -1 *.x | sed -e 's/\.x//'` ; do \
			if [ ! -f $${i}.h ] ; then \
				rpcgen -h $${i}.x -o $${i}.h; \
			fi; \
		done) 

.include <bsd.gnu.mk>
