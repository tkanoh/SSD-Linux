#	$ssdlinux: Makefile,v 1.1 2002/07/01 07:22:47 yamagata Exp $

.include <bsd.own.mk>

PROG=		dc
SRCS=		dc.c misc.c eval.c stack.c array.c numeric.c string.c

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

.PATH:		${DIST}/dc ${DIST}/doc

.include <bsd.prog.mk>
