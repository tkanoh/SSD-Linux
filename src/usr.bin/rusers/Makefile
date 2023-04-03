#	$ssdlinux: Makefile,v 1.2 2002/06/05 06:01:03 yamagata Exp $

.include <bsd.own.mk>

PROG=		rusers
SRCS=		rusers_xdr.c ${PROG}.c
CLEANFILES=	rusers.x rusers_xdr.c rusers.h

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rusers/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR} -DGNU_LIBC -D_GNU_SOURCE -D_NO_UT_TIME

rusers.x: 
	cp ${DESTDIR}/usr/include/rpcsvc/rusers.x rusers.x

rusers_xdr.c: rusers.x
	rm -f rusers_xdr.c rusers.h
	rpcgen -c -C -o rusers_xdr.c rusers.x
	rpcgen -h -o rusers.h rusers.x

NOGCCERROR=	yes

.include <bsd.prog.mk>
