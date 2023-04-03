#	$ssdlinux: Makefile,v 1.3 2002/06/11 09:28:31 yamagata Exp $

.include <bsd.own.mk>

PROG=		su		
SRCS=		${PROG}.c suauth.c
BINMODE=	4555

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
