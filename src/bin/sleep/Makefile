#	$ssdlinux: Makefile,v 1.8 2003/07/04 04:00:16 yamagata Exp $

.include <bsd.own.mk>

PROG=		sleep		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils
.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"
.if ${FULL_SHARED} == "yes"
LDADD+=		-lm -lrt
.else
LIBMDIR=	${.CURDIR}/../../lib/glibc-static/build/math
LDADD+=		-L${LIBMDIR} -lm
DPADD+=		${LIBMDIR}/libm.a
LIBRTDIR=	${.CURDIR}/../../lib/glibc-static/build/rt
LDADD+=		-L${LIBRTDIR} -lrt
DPADD+=		${LIBRTDIR}/librt.a
.endif

.include <bsd.prog.mk>
