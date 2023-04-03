#	$ssdlinux: Makefile,v 1.18 2003/12/04 10:19:31 kanoh Exp $
.include <bsd.own.mk>

CROSSDIR=	${DESTDIR}/usr/cross/powerpc
KERNSRCDIR=	/usr/src/linux
_TARGET=	powerpc-ssd-linux-gnu		

.MAIN: all
all: build

build:
	cd ${.CURDIR}/binutils && ${MAKE} HAVE_INCLUDE=1
	cd ${.CURDIR}/glibc && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/libtermcap && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/gcc && ${MAKE}
	cd ${.CURDIR}/gdb && ${MAKE}
	cd ${.CURDIR}/ginstall && ${MAKE}

initial_build:
	cd ${.CURDIR}/binutils && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/gcc-core && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/ginstall && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/glibc && ${MAKE} HAVE_SYSINCLUDE=1 && ${MAKE} install
	(cd ${CROSSDIR}/${_TARGET}/include && rm -f asm) 
	(cd ${CROSSDIR}/${_TARGET}/include && ln -sf ${KERNSRCDIR}/include/asm-ppc asm) 
	(cd ${CROSSDIR}/${_TARGET}/include && ln -sf ${KERNSRCDIR}/include/linux) 
	(cd ${CROSSDIR}/${_TARGET}/include && ln -sf ${KERNSRCDIR}/arch/ppc/platforms) 
	cd ${.CURDIR}/libtermcap && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/binutils && ${MAKE} clean && ${MAKE} HAVE_INCLUDE=1 && ${MAKE} install
	cd ${.CURDIR}/gcc && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/gdb && ${MAKE}

install:
	cd ${.CURDIR}/gcc && ${MAKE} install
	cd ${.CURDIR}/binutils && ${MAKE} install
	cd ${.CURDIR}/glibc && ${MAKE} install
	cd ${.CURDIR}/libtermcap && ${MAKE} install
	cd ${.CURDIR}/gdb && ${MAKE} install
	cd ${.CURDIR}/ginstall && ${MAKE} install
.ifdef DESTDIR
	mkdir -p ${CROSSDIR}/${_TARGET}/sys-include
	cp -f ${CROSSDIR}/${_TARGET}/include/limits.h ${CROSSDIR}/${_TARGET}/sys-include
	(cd ${CROSSDIR}/${_TARGET}/include && rm -f asm) 
	(cd ${CROSSDIR}/${_TARGET}/include && ln -sf ${KERNSRCDIR}/include/asm-ppc asm) 
	(cd ${CROSSDIR}/${_TARGET}/include && ln -sf ${KERNSRCDIR}/include/linux) 
	(cd ${CROSSDIR}/${_TARGET}/include && ln -sf ${KERNSRCDIR}/arch/ppc/platforms) 
.endif

cleandir: clean

clean:
.if !defined(NOCLEAN) || defined(FORCE_CLEAN)
	cd ${.CURDIR}/binutils && ${MAKE} clean
	cd ${.CURDIR}/gcc-core && ${MAKE} clean
	cd ${.CURDIR}/glibc && ${MAKE} clean
	cd ${.CURDIR}/gcc && ${MAKE} clean
	cd ${.CURDIR}/gdb && ${MAKE} clean
	cd ${.CURDIR}/libtermcap && ${MAKE} clean
	cd ${.CURDIR}/ginstall && ${MAKE} clean
.endif
