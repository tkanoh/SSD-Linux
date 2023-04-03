#	$ssdlinux: Makefile,v 1.11 2004/06/16 04:04:10 yamagata Exp $

.include <bsd.own.mk>

PROG=		sed
# sed
SRCS=		${PROG}.c compile.c execute.c regexp.c fmt.c mbcs.c
# lib
SRCS+=		utils.c regex.c
MKMAN=		no
CLEANFILES=	regex.h

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST}/${PROG} ${DIST}/lib

CPPFLAGS+=	-DNO_USAGE
CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-I${.CURDIR}/../../../usr.bin/${PROG}/include
CPPFLAGS+=	-I${DIST}/${PROG}
CPPFLAGS+=	-I${DIST}
CPPFLAGS+=	-I${DIST}/lib
CPPFLAGS+=	-I${.CURDIR}/../../i386/ramdiskbin/${PROG}

regex.c: regex.h

regex.h: ${DIST}/lib/regex_.h
	rm -f ${.TARGET}
	cp ${DIST}/lib/regex_.h ${.TARGET}

proginstall:

NOGCCERROR=	yes

.include <bsd.prog.mk>
