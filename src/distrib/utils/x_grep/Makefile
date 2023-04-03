#	$ssdlinux: Makefile,v 1.5 2004/11/01 08:47:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		grep
SRCS=		grep.c dfa.c kwset.c obstack.c savedir.c getopt.c getopt1.c search.c grepmat.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/grep
.PATH:		${DIST}/src ${DIST}/lib

CPPFLAGS+=	-DNO_USAGE
CPPFLAGS+=	-I${.CURDIR}/../../../usr.bin/grep -I${DIST}/src -I${DIST}/lib
CPPFLAGS+=	-DHAVE_CONFIG_H -DLOCALEDIR=\"/usr/share/locale\"

NOGCCERROR=	yes

proginstall:

.include <bsd.prog.mk>
