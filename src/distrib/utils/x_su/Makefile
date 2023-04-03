#	$ssdlinux: Makefile,v 1.4 2002/06/12 03:27:05 yamagata Exp $

.include <bsd.own.mk>

PROG=		su		
SRCS=		${PROG}.c suauth.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/shadow
.PATH:		${DIST}/src

FORCE_NO_PAM=	yes
.include "${.CURDIR}/../../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

proginstall:

.include <bsd.prog.mk>
