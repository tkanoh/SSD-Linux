#	$ssdlinux: Makefile,v 1.3 2003/09/11 09:04:17 yamagata Exp $

.include <bsd.own.mk>

PROG=		gawk
SRCS=		eval.c profile.c

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

MLINKS=         ${PROG}.1 p${PROG}.1
SYMLINKS+=	${BINDIR}/${PROG} ${BINDIR}/awk

.include <bsd.prog.mk>
