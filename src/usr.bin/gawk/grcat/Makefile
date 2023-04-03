#	$ssdlinux: Makefile,v 1.1 2002/07/02 05:17:16 yamagata Exp $

.include <bsd.own.mk>

PROG=		grcat
BINDIR=		/usr/libexec/awk
MKMAN=		no

.include "${.CURDIR}/../Makefile.cflags"

.PATH:		${DIST}/awklib/eg/lib

CPPFLAGS=	-O2
LDADD=		-rdynamic

.include <bsd.prog.mk>
