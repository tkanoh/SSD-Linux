#	$ssdlinux: Makefile,v 1.10 2003/07/04 03:53:17 yamagata Exp $

.include <bsd.own.mk>

PROG=		date		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"
.if ${FULL_SHARED} == "yes"
LDADD+=		-lrt
.else
LIBRTDIR=	${.CURDIR}/../../lib/glibc-static/build/rt
LDADD+=		-L${LIBRTDIR} -lrt
DPADD+=		${LIBRTDIR}/librt.a
.endif

.include <bsd.prog.mk>
