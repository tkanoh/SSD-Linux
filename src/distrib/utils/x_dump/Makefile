#	$ssdlinux: Makefile,v 1.5 2003/11/04 06:08:07 yamagata Exp $

.include <bsd.own.mk>

PROG=		dump
SRCS=		itime.c main.c optr.c tape.c traverse.c unctime.c dumprmt.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/dump
.PATH:		${DIST}/common ${DIST}/dump ${DIST}/compat/lib

.include "${.CURDIR}/../../../lib/dump/Makefile.cflags"
.include "${.CURDIR}/../../../lib/dump/Makefile.ldflags"
CPPFLAGS+=	-DNO_USAGE

NOGCCERROR=	yes

.include <bsd.prog.mk>
