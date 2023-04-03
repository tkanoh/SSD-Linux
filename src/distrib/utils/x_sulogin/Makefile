#	$ssdlinux: Makefile,v 1.3 2002/06/12 03:28:02 yamagata Exp $

.include <bsd.own.mk>

PROG=		sulogin		
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/shadow
.PATH:		${DIST}/src

FORCE_NO_PAM=	yes
.include "${.CURDIR}/../../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

proginstall:

.include <bsd.prog.mk>
