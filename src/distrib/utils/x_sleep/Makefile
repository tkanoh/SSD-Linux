#	$ssdlinux: Makefile,v 1.1 2004/03/23 14:15:16 yamagata Exp $

.include <bsd.own.mk>

PROG=		sleep
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/coreutils50
.PATH:		${DIST}/src

LIBCUDIR=	${.CURDIR}/../../../lib/coreutils50
CPPFLAGS+=	-DNO_USAGE
.include "${LIBCUDIR}/Makefile.cflags"

proginstall:

.include <bsd.prog.mk>
