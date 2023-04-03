#	$ssdlinux: Makefile,v 1.2 2002/06/05 06:02:36 yamagata Exp $

.include <bsd.own.mk>

PROG=		rwall
SRCS=		dummy.c ${PROG}.c
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
