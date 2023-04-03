#	$ssdlinux: Makefile,v 1.3 2002/06/06 07:45:00 yamagata Exp $

.include <bsd.own.mk>

PROG=		callbootd
SRCS=		bootparam_prot_xdr.c callbootd.c bootparam_prot_clnt.c
MKMAN=		no
CLEANFILES=	bootparam_prot.x bootparam_prot_xdr.c bootparam_prot.h \
		bootparam_prot_clnt.c

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-bootparamd/rpc.bootparamd
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

NOGCCERROR=	yes

CPPFLAGS+=	-Wall -W -Wpointer-arith -Wbad-function-cast -Wcast-qual \
		-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
		-Wnested-externs -Winline -I${DIST} -I${.CURDIR}

.include "${LIBINET6}/Makefile.ldflags"

bootparam_prot.x: bootparam_prot.x.real
	cp ${DIST}/bootparam_prot.x.real bootparam_prot.x

bootparam_prot_xdr.c: bootparam_prot.x
	rm -f bootparam_prot_xdr.c
	rpcgen -c bootparam_prot.x -o bootparam_prot_xdr.c
	rpcgen -h bootparam_prot.x -o bootparam_prot.h

bootparam_prot_clnt.c: bootparam_prot.x
	rm -f bootparam_prot_clnt.c
	rpcgen -l bootparam_prot.x -o bootparam_prot_clnt.c

.include <bsd.prog.mk>
