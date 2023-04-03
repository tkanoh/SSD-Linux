#	$ssdlinux: Makefile,v 1.18 2004/11/10 06:38:27 yamagata Exp $

.include "${.CURDIR}/../../share/mk/bsd.own.mk"
.include "${.CURDIR}/../Makefile.inc"

DISTNAME=	gdb-
DISTVERSION=	6.3
EXTRACT_SUFX=	tar.bz2
GNU_DIST=	yes
LOCAL_PATCHFILES=	${DISTNAME}DESTDIR.patch

# enable to cross compile
LOCAL_PATCHFILES+=	${DISTNAME}bfd.patch
LOCAL_PATCHFILES+=	${DISTNAME}libiberty.patch
LOCAL_PATCHFILES+=	${DISTNAME}opcodes.patch
LOCAL_PATCHFILES+=	${DISTNAME}readline.patch

DEPENDENT=	usr.bin/gdb
DEPENDENT+=	cross/powerpc/gdb

.include "${.CURDIR}/../../share/mk/bsd.mkdist.mk"
