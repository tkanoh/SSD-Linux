#	$ssdlinux: Makefile,v 1.3 2002/06/06 06:24:03 yamagata Exp $

.include <bsd.own.mk>

PROG=		rpc.bootparamd
SRCS=		bootparam_prot_svc.c bootparam_prot_xdr.c rpc.bootparamd.c main.c
MAN=		bootparamd.8 bootparams.5
CLEANFILES=	bootparam_prot.x bootparam_prot.h bootparam_prot_svc.c \
		bootparam_prot_xdr.c

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-bootparamd/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${DIST} -I${.CURDIR}

NOGCCERROR=	yes

bootparam_prot.x: bootparam_prot.x.real
	cp ${DIST}/bootparam_prot.x.real bootparam_prot.x

bootparam_prot_svc.c: bootparam_prot.x
	rm -f bootparam_prot_svc.c bootparam_prot.h
	rpcgen -m bootparam_prot.x -o bootparam_prot_svc.c
	rpcgen -h bootparam_prot.x -o bootparam_prot.h

bootparam_prot_xdr.c: bootparam_prot.x
	rm -f bootparam_prot_xdr.c
	rpcgen -c bootparam_prot.x -o bootparam_prot_xdr.c

MLINKS=		bootparamd.8 ${PROG}.8

.include <bsd.prog.mk>
