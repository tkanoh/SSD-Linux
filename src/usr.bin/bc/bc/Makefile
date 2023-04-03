#	$ssdlinux: Makefile,v 1.1 2002/07/01 07:22:47 yamagata Exp $

.include <bsd.own.mk>

PROG=		bc
SRCS=		main.c bc.c scan.c execute.c load.c storage.c util.c global.c

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

.PATH:		${DIST}/bc ${DIST}/doc

NOGCCERROR=	yes

.include <bsd.prog.mk>
