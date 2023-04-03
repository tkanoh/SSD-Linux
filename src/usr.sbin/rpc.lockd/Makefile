#	$ssdlinux: Makefile,v 1.4 2003/09/04 08:16:04 yamagata Exp $

.include <bsd.own.mk>

PROG=		rpc.lockd
SRCS=		lockd.c
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/nfs-utils
.PATH:		${DIST}/utils/lockd

.include "${.CURDIR}/../../lib/nfs-utils/Makefile.cflags"
.include "${.CURDIR}/../../lib/nfs-utils/Makefile.ldflags"

${MAN}:
	cp ${DIST}/utils/lockd/lockd.man ${.TARGET}

.include <bsd.prog.mk>
