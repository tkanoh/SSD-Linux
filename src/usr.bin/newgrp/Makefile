#	$ssdlinux: Makefile,v 1.2 2002/06/05 03:54:56 yamagata Exp $

.include <bsd.own.mk>

PROG=		newgrp		
BINMODE=	4555

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

SYMLINKS=	${BINDIR}/${PROG} ${BINDIR}/sg

.include <bsd.prog.mk>
