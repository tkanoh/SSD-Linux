#	$ssdlinux: Makefile,v 1.2 2003/11/04 06:04:45 yamagata Exp $
.include <bsd.own.mk>

LIB=    compat
SRCS=	compaterr.c compatglob.c bylabel.c system.c rmtflags.c minilzo.c
MKMAN=	no

DIST=	${.CURDIR}/../../dist/dump
.PATH:	${DIST}/compat/lib

.include "${.CURDIR}/Makefile.cflags"

libinstall::

.include <bsd.lib.mk>
