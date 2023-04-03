#	$ssdlinux: Makefile,v 1.2 2002/06/06 07:40:57 yamagata Exp $

.include <bsd.own.mk>

PROG=		nsupdate
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../../dist/bind
.PATH:		${DIST}/bin/${PROG}

CPPFLAGS+=	-I${DIST}/bin/${PROG}/include

LIBBINDDIR=	${.CURDIR}/../../../lib/bind
.include "${LIBBINDDIR}/Makefile.cflags"

.include <bsd.prog.mk>
