#	$ssdlinux: Makefile,v 1.2 2002/06/18 06:15:19 yamagata Exp $

.include <bsd.own.mk>

PROG=		rpc.rquotad
SRCS=		rquota_server.c rquota_svc.c rquota_xdr.c quotactl.c hasquota.c
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/nfs-utils
.PATH:		${DIST}/utils/rquotad

.include "${.CURDIR}/../../lib/nfs-utils/Makefile.cflags"
.include "${.CURDIR}/../../lib/nfs-utils/Makefile.ldflags"

${MAN}:
	cp ${DIST}/utils/rquotad/rquotad.man ${.TARGET}

NOGCCERROR=	yes

.include <bsd.prog.mk>
