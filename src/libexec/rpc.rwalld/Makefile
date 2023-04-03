#	$ssdlinux: Makefile,v 1.3 2002/06/18 06:19:07 yamagata Exp $

.include <bsd.own.mk>

PROG=		rpc.rwalld
SRCS=		dummy.c rwalld.c daemon.c
MAN=		${PROG}.8 daemon.3
CLEANFILES=	rwall.x rwall.h dummy.c

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rwall
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${DIST}/${PROG} -I${.CURDIR}

NOGCCERROR=	yes

rwall.x:
	cp ${DIST}/include/rpcsvc/rwall.x rwall.x

dummy.c: rwall.x
	rm -f rwall.h
	rpcgen -h -o rwall.h rwall.x
	touch dummy.c

.include <bsd.prog.mk>
