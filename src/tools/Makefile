#	$ssdlinux: Makefile,v 1.16 2002/12/26 10:45:51 kanoh Exp $
.include "${.CURDIR}/../share/mk/bsd.own.mk"

KERNSRCDIR=	/usr/src/linux
.if ${TARGET_HOSTTYPE} == "powerpc"
_HOSTTYPE=	ppc
.else
_HOSTTYPE=	i386
.endif

.MAIN: all
all: build

build:
	cd ${.CURDIR}/binutils && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/gcc-core && ${MAKE} && ${MAKE} install
	(cd ${TOOLCHAINDIR}/include && ln -sf ${KERNSRCDIR}/include/asm) 
	(cd ${TOOLCHAINDIR}/include && ln -sf ${KERNSRCDIR}/include/linux) 
	(cd ${TOOLCHAINDIR}/include && ln -sf ${KERNSRCDIR}/arch/${_HOSTTYPE}/platforms) 
	cd ${.CURDIR}/glibc && ${MAKE} && ${MAKE} install
	cd ${.CURDIR}/gcc && ${MAKE} && ${MAKE} install
	(cd ${TOOLCHAINDIR}/${MACHTYPE}${NEW_GLIBC} && ln -sf sys-include include)

install:

cleandir: clean

clean:
.if !defined(NOCLEAN) || defined(FORCE_CLEAN)
	cd ${.CURDIR}/binutils &&  ${MAKE} clean
	cd ${.CURDIR}/gcc-core &&  ${MAKE} clean
	cd ${.CURDIR}/glibc &&  ${MAKE} clean
	cd ${.CURDIR}/gcc &&  ${MAKE} clean
	rm -rf ${TOOLCHAINDIR}
.endif
