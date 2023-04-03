#	$ssdlinux: Makefile,v 1.10 2004/06/15 15:13:54 kanoh Exp $

.include <bsd.own.mk>

DISTNAME=	gcc
HAVE_DESTDIR=	1
CONFIGURE_FULL_PREFIX= 1
CONFIGURE_ENV=	CFLAGS="-O2" CXXFLAGS="-O2" LDFLAGS=-s
CONFIGURE_OPTIONS= --enable-shared --with-gnu-ld --enable-threads --verbose \
			--enable-languages=c,c++ --build=${MACHTYPE}
GMAKE_ENV=
GMAKE_OPTIONS=
GMAKE_INSTALL_OPTIONS= DESTDIR=${DESTDIR}
INSTALL_STRIP=	no

# need when compile glibc, see glibc/sunrpc/Makefile 
SYMLINKS+=	${BINDIR}/cpp /lib/cpp
LINKS+= 	${BINDIR}/gcc ${BINDIR}/cc

.ifdef CROSS_BUILD
SYSLIMITS_H=lib/gcc-lib/${TARGET_MACHTYPE}/${GCC_VERSION}/include/syslimits.h
POSTBUILD_SCRIPT=	if [ ! -f ${.CURDIR}/build/gcc/specs.orig ] ; then \
				mv ${.CURDIR}/build/gcc/specs ${.CURDIR}/build/gcc/specs.orig; \
			fi; \
			sed -e 's/^1/0/' ${.CURDIR}/build/gcc/specs.orig > ${.CURDIR}/build/gcc/specs
POSTINSTALL_SCRIPT=	if [ ! -f ${DESTDIR}/usr/${SYSLIMITS_H} ] ; then \
				cp /usr/cross/${CROSS_BUILD}/${SYSLIMITS_H} \
					${DESTDIR}/usr/${SYSLIMITS_H}; \
			fi
.endif

.ifdef NEW_GLIBC
SYSLIMITS_H=lib/gcc-lib/${TARGET_MACHTYPE}${NEW_GLIBC}/${GCC_VERSION}/include/syslimits.h
POSTBUILD_SCRIPT=	if [ ! -f ${.CURDIR}/build/gcc/specs.orig ] ; then \
				mv ${.CURDIR}/build/gcc/specs ${.CURDIR}/build/gcc/specs.orig; \
			fi; \
			sed -e 's/^1/0/' ${.CURDIR}/build/gcc/specs.orig > ${.CURDIR}/build/gcc/specs
POSTINSTALL_SCRIPT=	if [ ! -f ${DESTDIR}/usr/${SYSLIMITS_H} ] ; then \
				cp ${TOOLCHAINDIR}/${SYSLIMITS_H} \
					${DESTDIR}/usr/${SYSLIMITS_H}; \
			fi
.endif

.include <bsd.gnu.mk>
