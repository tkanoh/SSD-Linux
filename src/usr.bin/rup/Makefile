#	$ssdlinux: Makefile,v 1.3 2002/06/07 00:58:43 yamagata Exp $

.include <bsd.own.mk>

PROG=		rup
SRCS=		${PROG}.c rstat_xdr.c err.c
MAN=		${PROG}.1 err.3
CLEANFILES=	rusers.x rstat_xdr.c rstat.h rstat.x

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rusers/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-DGNU_LIBC -D_GNU_SOURCE -D_NO_UT_TIME

rstat.x: 
	cp ${DESTDIR}/usr/include/rpcsvc/rstat.x rstat.x

rstat_xdr.c: rstat.x
	rm -f rstat_xdr.c rstat.h
	rpcgen -c -C -o rstat_xdr.c rstat.x
	rpcgen -h -o rstat.h rstat.x

NOGCCERROR=	yes

.include <bsd.prog.mk>
