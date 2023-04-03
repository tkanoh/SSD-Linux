#	$ssdlinux: Makefile,v 1.3 2002/06/18 06:17:26 yamagata Exp $

.include <bsd.own.mk>

PROG=		rpc.rusersd
SRCS=		rusers_xdr.c rusersd.c rusers_proc.c daemon.c
MAN=		${PROG}.8 daemon.3
CLEANFILES=	rusers.x rusers_xdr.c rusers.h

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rusers/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-DGNU_LIBC -D_GNU_SOURCE -D_NO_UT_TIME

NOGCCERROR=	yes

rusers.x: 
	cp ${DESTDIR}/usr/include/rpcsvc/rusers.x rusers.x

rusers_xdr.c: rusers.x
	rm -f rusers_xdr.c rusers.h
	rpcgen -c -C -o rusers_xdr.c rusers.x
	rpcgen -h -o rusers.h rusers.x

.include <bsd.prog.mk>
