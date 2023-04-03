#	$ssdlinux: Makefile,v 1.3 2003/09/04 08:20:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		rpc.statd
SRCS=		sm_inter_clnt.c sm_inter_svc.c sm_inter_xdr.c  callback.c \
		notlist.c log.c misc.c monitor.c notify.c simu.c stat.c \
		statd.c state.c svc_run.c rmtcall.c
MAN=		${PROG}.8
CLEANFILES=	${MAN} sm_inter.x sm_inter.h sm_inter_clnt.c sm_inter_svc.c \
		sm_inter_xdr.c

DIST=		${.CURDIR}/../../dist/nfs-utils
.PATH:		${DIST}/utils/statd

.include "${.CURDIR}/../../lib/nfs-utils/Makefile.cflags"
.include "${.CURDIR}/../../lib/nfs-utils/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR}

${MAN}:
	cp ${DIST}/utils/statd/statd.man ${.TARGET}

sm_inter_clnt.c: sm_inter.h
	rm -f ${.TARGET}
	rpcgen -l -o ${.TARGET} sm_inter.x

sm_inter_svc.c:
	rm -f ${.TARGET}
	rpcgen -m -o ${.TARGET} sm_inter.x

sm_inter_xdr.c:
	rm -f ${.TARGET}
	rpcgen -c -o ${.TARGET} sm_inter.x

sm_inter.h:
	rm -f ${.TARGET}
	cp ${DIST}/utils/statd/sm_inter.x .
	rpcgen -h -o ${.TARGET} sm_inter.x

NOGCCERROR=	yes

.include <bsd.prog.mk>
