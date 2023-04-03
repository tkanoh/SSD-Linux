#	$ssdlinux: Makefile,v 1.14 2003/07/04 04:04:11 yamagata Exp $

.include <bsd.own.mk>

PROG=		uname		

DIST=		${.CURDIR}/../../dist/coreutils
.PATH:		${DIST}/src ${DIST}/man

LIBCUDIR=	${.CURDIR}/../../lib/coreutils

CPPFLAGS+=	-DUSERLAND="\"SSD/Linux ${SSDRELEASENAME}\""
.if ${TARGET_SSDHOSTTYPEX} == "powerpc-obs2xx"
CPPFLAGS+=	-DPROCESSOR_TYPE="\"ppc405\""
CPPFLAGS+=	-DHARDWARE_PLATFORM_TYPE="\"OpenBlockS\""
.endif
.if ${TARGET_SSDHOSTTYPE} == "powerpc-obs50"
CPPFLAGS+=	-DPROCESSOR_TYPE="\"mpc860\""
CPPFLAGS+=	-DHARDWARE_PLATFORM_TYPE="\"OpenBlockS\""
.endif

.include "${LIBCUDIR}/Makefile.cflags"
.include "${LIBCUDIR}/Makefile.ldflags"

.include <bsd.prog.mk>
