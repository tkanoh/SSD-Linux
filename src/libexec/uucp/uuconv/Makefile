#	$ssdlinux: Makefile,v 1.2 2003/06/12 08:52:42 yamagata Exp $

.include <bsd.own.mk>

PROG=		uuconv
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/uucp
.PATH:		${DIST}

.include "${.CURDIR}/../../../lib/uucp/Makefile.cflags"

CPPFLAGS+=	-I${DIST}/uuconf

.include <bsd.prog.mk>
