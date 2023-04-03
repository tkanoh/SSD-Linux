#	$ssdlinux: Makefile,v 1.108 2004/11/04 14:35:07 kanoh Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=		linux-
DISTVERSION=		ppc-${KERNEL_MAJOR}.${KERNEL_MINOR}.${KERNEL_PATCHLEVEL}
EXTRACT_SUFX=		tar.bz2
VERSIONS_FILE:=		${DISTDIR}/VERSIONS
DISTDIR=		${SSDSRCDIR}
ALTRENAMEDISTDIR=	( cd ${SSDSRCDIR} && ln -s linux-${KERNEL_VERSION} linux ) 
CLEAN_ALTRENAMEDISTDIR= rm -rf ${KERNSRCDIR} ${KERNSRCDIR}-*
DEPENDENT=	linux

.include "${.CURDIR}/${KERNEL_DIFF_PATH}/Makefile.inc"

.ifdef ALT_KERNEL_CONFIG
.if exists(${.CURDIR}/${KERNEL_DIFF_PATH}/${_ALT_KERNEL_CONFIG})
KERNEL_CONFIG?= ${.CURDIR}/${KERNEL_DIFF_PATH}/${_ALT_KERNEL_CONFIG}
.elif exists(${.CURDIR}/${KERNEL_VERSION}/${_ALT_KERNEL_CONFIG})
KERNEL_CONFIG?= ${.CURDIR}/${KERNEL_VERSION}/${_ALT_KERNEL_CONFIG}
.elif exists(${.CURDIR}/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG})
KERNEL_CONFIG?=	${.CURDIR}/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG}
.else
KERNEL_CONFIG?= ${.CURDIR}/${KERNEL_VERSION}/${_KERNEL_CONFIG}
.endif
.else
.if exists(${.CURDIR}/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG})
KERNEL_CONFIG?=	${.CURDIR}/${KERNEL_DIFF_PATH}/${_KERNEL_CONFIG}
.else
KERNEL_CONFIG?= ${.CURDIR}/${KERNEL_VERSION}/${_KERNEL_CONFIG}
.endif
.endif

# for IPv6
.if ${IPV6} == "yes"
DISTRELEASE=	${_DISTRELEASE}-ipv6
.else
DISTRELEASE=	${_DISTRELEASE}
.endif

POSTEXTRACT=	(cd ${KERNSRCDIR} && make symlinks); \
		(cd ${KERNSRCDIR} && make include/linux/version.h); \
		if [ -f ${KERNEL_CONFIG} ]; then \
			cp ${KERNEL_CONFIG} ${KERNSRCDIR}/.config; \
		fi; \
		if [ -d ${KERNSRCDIR}/arch/ppc/platforms ]; then \
			rm -f /usr/include/platforms; \
			(cd /usr/include && ln -s ${KERNSRCDIR}/arch/ppc/platforms); \
		fi; \
		if [ -d /usr/cross/powerpc/powerpc-ssd-linux-gnu/include ]; then \
			(cd /usr/cross/powerpc/powerpc-ssd-linux-gnu/include && \
				rm -f asm); \
			(cd /usr/cross/powerpc/powerpc-ssd-linux-gnu/include && \
				ln -sf ${KERNSRCDIR}/include/asm-ppc asm); \
			(cd /usr/cross/powerpc/powerpc-ssd-linux-gnu/include && \
				ln -sf ${KERNSRCDIR}/include/linux); \
			(cd /usr/cross/powerpc/powerpc-ssd-linux-gnu/include && \
				ln -sf ${KERNSRCDIR}/arch/ppc/platforms); \
		fi

backup-config:
		cp ${KERNSRCDIR}/.config ${KERNEL_CONFIG}

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
