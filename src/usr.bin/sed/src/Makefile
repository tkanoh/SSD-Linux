#	$ssdlinux: Makefile,v 1.8 2004/06/16 03:59:17 yamagata Exp $

.include <bsd.own.mk>

PROG=		sed
SRCS=		${PROG}.c compile.c execute.c regexp.c fmt.c mbcs.c

DIST=		${.CURDIR}/../../../dist/${PROG}
.PATH:		${DIST}/${PROG} ${DIST}/doc

CPPFLAGS+=	-DHAVE_CONFIG_H
CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-I${.CURDIR}/../include
CPPFLAGS+=	-I${DIST}
CPPFLAGS+=	-I${DIST}/lib

LDADD+=         -L${.CURDIR}/../lib -lsed
DPADD+=         ${.CURDIR}/../lib/libsed.a

.include <bsd.prog.mk>
