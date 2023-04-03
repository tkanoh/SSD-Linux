#	$ssdlinux: Makefile,v 1.12 2005/01/27 02:00:36 yamagata Exp $

.include 	<bsd.own.mk>

PROG=		restore
SRCS=		dirs.c interactive.c main.c restore.c symtab.c tape.c utilities.c dumprmt.c
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/dump
.PATH:		${DIST}/common ${DIST}/${PROG}

.include "${.CURDIR}/../../lib/dump/Makefile.cflags"
.include "${.CURDIR}/../../lib/dump/Makefile.ldflags"

.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=      -I${DIST}/../readline/..
.endif
LDADD+=		-L${LIBSRCDIR}/readline/readline -lreadline
LDADD+=		-L${LIBSRCDIR}/libtermcap -ltermcap

${MAN}:
	sed -e "s|__DUMPDATES__|/etc/dumpdates|g" \
	    -e "s|__DATE__|January 21, 2005|g" \
	    -e "s|__VERSION__|0.4b39|g" ${DIST}/${PROG}/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
