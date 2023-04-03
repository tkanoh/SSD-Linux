#	$ssdlinux: Makefile,v 1.3 2004/02/25 07:40:43 yamagata Exp $

.include <bsd.own.mk>

PROG=		login		
SRCS=		login.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/shadow
.PATH:		${DIST}/src

FORCE_NO_PAM=	yes
.include "${.CURDIR}/../../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

proginstall:

.include <bsd.prog.mk>
