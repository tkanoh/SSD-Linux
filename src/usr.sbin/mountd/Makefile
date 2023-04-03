#	$ssdlinux: Makefile,v 1.6 2003/09/04 08:21:29 yamagata Exp $

.include <bsd.own.mk>

PROG=		mountd
SRCS=		${PROG}.c mount_dispatch.c auth.c rmtab.c cache.c svc_run.c
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/nfs-utils
.PATH:		${DIST}/utils/${PROG}

.include "${.CURDIR}/../../lib/nfs-utils/Makefile.cflags"
.include "${.CURDIR}/../../lib/nfs-utils/Makefile.ldflags"

${MAN}:
	cp ${DIST}/utils/${PROG}/${PROG}.man ${.TARGET}

NOGCCERROR=	yes

.include <bsd.prog.mk>
