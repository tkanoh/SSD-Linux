#	$ssdlinux: Makefile,v 1.4 2002/12/29 15:24:44 kanoh Exp $

.include <bsd.own.mk>

PROG=		depmod
MAN=		${PROG}.8

# force shared
LDSTATIC=

DIST=		${.CURDIR}/../../dist/modutils
.PATH:		${DIST}/${PROG} ${DIST}/man

.include "${.CURDIR}/../../lib/modutils/Makefile.cflags"

LDADD+=		-L${LIBMODU}/libobj -lobj
LDADD+=		-L${LIBMODU}/libutil -lutil
LDADD+=		-L${LIBMODU}/../libz -lz
DPADD+=		${LIBMODU}/libobj/libobj.a
DPADD+=		${LIBMODU}/libutil/libutil.a

.include <bsd.prog.mk>
