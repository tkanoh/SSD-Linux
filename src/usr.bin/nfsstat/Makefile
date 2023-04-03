#	$ssdlinux: Makefile,v 1.2 2002/06/06 09:22:02 yamagata Exp $

.include 	<bsd.own.mk>

PROG=		nfsstat
MAN=		${PROG}.1
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/nfs-utils
.PATH:		${DIST}/utils/${PROG}

.include "${.CURDIR}/../../lib/nfs-utils/Makefile.cflags"
.include "${.CURDIR}/../../lib/nfs-utils/Makefile.ldflags"

${MAN}:
	cp ${DIST}/utils/${PROG}/${PROG}.man ${.TARGET}

.include <bsd.prog.mk>
