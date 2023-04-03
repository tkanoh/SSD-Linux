#	$ssdlinux: Makefile,v 1.11 2005/01/27 02:00:52 yamagata Exp $

.include <bsd.own.mk>

PROG=		dump
SRCS=		itime.c main.c optr.c tape.c traverse.c unctime.c dumprmt.c
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}/common ${DIST}/${PROG}

.include "${.CURDIR}/../../lib/${PROG}/Makefile.cflags"
.include "${.CURDIR}/../../lib/${PROG}/Makefile.ldflags"

${MAN}:
	sed -e "s|__DUMPDATES__|/etc/dumpdates|g" \
	    -e "s|__DATE__|January 21, 2005|g" \
	    -e "s|__VERSION__|0.4b39|g" ${DIST}/${PROG}/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
