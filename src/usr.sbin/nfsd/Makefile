#	$ssdlinux: Makefile,v 1.3 2003/09/04 08:14:36 yamagata Exp $

.include <bsd.own.mk>

PROG=		nfsd
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/nfs-utils
.PATH:		${DIST}/utils/${PROG}

.include "${.CURDIR}/../../lib/nfs-utils/Makefile.cflags"
.include "${.CURDIR}/../../lib/nfs-utils/Makefile.ldflags"

${MAN}:
	cp ${DIST}/utils/${PROG}/${PROG}.man ${.TARGET}

.include <bsd.prog.mk>
