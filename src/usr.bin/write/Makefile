#	$ssdlinux: Makefile,v 1.3 2004/01/22 09:44:40 yamagata Exp $

.include <bsd.own.mk>

PROG=		write

BINMODE=	2555
BINGRP=		tty

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netwrite
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${DIST}/${PROG}

.include <bsd.prog.mk>
