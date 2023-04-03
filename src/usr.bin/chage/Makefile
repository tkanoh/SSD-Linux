#	$ssdlinux: Makefile,v 1.3 2002/07/29 02:15:51 yamagata Exp $

.include <bsd.own.mk>

PROG=		chage		
BINMODE=	4555

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

USE_PAM=	no

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
