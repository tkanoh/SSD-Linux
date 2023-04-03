#	$ssdlinux: Makefile.inc,v 1.10 2004/07/04 05:56:44 yamagata Exp $
#	$NetBSD: Makefile.inc,v 1.5 2001/08/08 14:59:26 wiz Exp $

.if !defined(__MAKEFILE_INC_INCLUDED__)
__MAKEFILE_INC_INCLUDED__=1

.include <bsd.own.mk>

DIST=		${.CURDIR}/../../../dist

CPPFLAGS+=	-I${.CURDIR}/../common -I${DIST}/texinfo/lib \
		-DLOCALEDIR=\"/usr/share/locale\" -DHAVE_CONFIG_H
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DINTDIV0_RAISES_SIGFPE=1
.else ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DINTDIV0_RAISES_SIGFPE=0
.endif
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/termcap
.endif

LIBCOMMONDIR!=	cd ${.CURDIR}/../common && ${PRINTOBJDIR}
DPADD+=		${LIBCOMMONDIR}/libcommon.a
LDADD+=		-L${LIBCOMMONDIR} -lcommon

.if exists(${.CURDIR}/../../Makefile.inc)
.include "${.CURDIR}/../../Makefile.inc"
.endif

.endif # __MAKEFILE_INC_INCLUDED__
