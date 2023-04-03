#	$ssdlinux: Makefile,v 1.1 2005/02/25 07:04:56 yamagata Exp $

.include <bsd.own.mk>

LIB=		grep
SRCS=		kwset.c dfa.c m-common.c m-fgrep.c m-regex.c hard-locale.c
MKPIC=		no
MKPROFILE=	no
MKLINT=		no

.include "${.CURDIR}/../Makefile.inc"
.PATH:		${DIST}/gettext/gettext-tools/libgrep
CPPFLAGS+=	-DHAVE_CONFIG_H -I${.CURDIR}/../include
CPPFLAGS+=	-I${DIST}/gettext/gettext-tools/lib

libinstall::

.include <bsd.lib.mk>
