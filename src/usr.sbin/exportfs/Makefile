#	$ssdlinux: Makefile,v 1.3 2003/09/04 08:11:30 yamagata Exp $

.include <bsd.own.mk>

PROG=		exportfs
MAN=		${PROG}.8 exports.5
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/nfs-utils
.PATH:		${DIST}/utils/${PROG}

.include "${.CURDIR}/../../lib/nfs-utils/Makefile.cflags"
.include "${.CURDIR}/../../lib/nfs-utils/Makefile.ldflags"

${PROG}.8:
	cp ${DIST}/utils/${PROG}/${PROG}.man ${.TARGET}

exports.5:
	cp ${DIST}/utils/${PROG}/exports.man ${.TARGET}

.include <bsd.prog.mk>
