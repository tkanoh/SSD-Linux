#	$ssdlinux: Makefile,v 1.23 2004/12/15 08:35:24 todoroki Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	glibc-
DISTVERSION=	${GLIBC_VERSION}
ADDFILES=	glibc-linuxthreads-${DISTVERSION}.tar.gz
GNU_DIST=	yes

.if ${DISTVERSION} == "2.3.3"
EXTRACT_SUFX=	tar.bz2
ADDFILES=	glibc-linuxthreads-${DISTVERSION}.tar.bz2
.endif

.if ${DISTVERSION} == "2.3.2"
LOCAL_PATCHFILES=	glibc-2.3.2-sscanf_c.diff
DISTRELEASE=    0
.endif

.if ${DISTVERSION} == "2.3.1"
LOCAL_PATCHFILES= 	CA-2003-10.diff
.if ${TARGET_OPENBLOCKS} == "none"
LOCAL_PATCHFILES+=	ldconfig-bug-on-gcc.diff
DISTRELEASE=    2
.else
DISTRELEASE=	1
.endif
.endif

.if ${DISTVERSION} == "2.2.5"
LOCAL_PATCHFILES= 	glibc-${DISTVERSION}-resolv.diff
LOCAL_PATCHFILES+=	glibc-${DISTVERSION}-xdr_array_c.patch
LOCAL_PATCHFILES+=	libc-${DISTVERSION}-weak-alias-order.patch
DISTRELEASE=	8
.endif

DEPENDENT=	lib/glibc lib/glibc-static
DEPENDENT+=	cross/powerpc/glibc
DEPENDENT+=	tools/glibc
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/mtree.conf_in/common
DEPENDENT+=	distrib/powerpc-obs2xx/standard/initrd/list_in/cfbin

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
