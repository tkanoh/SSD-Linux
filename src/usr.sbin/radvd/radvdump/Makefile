#	$ssdlinux: Makefile,v 1.1 2002/07/05 09:34:17 yamagata Exp $

.include <bsd.own.mk>

PROG=		radvdump
MAN=		${PROG}.8
CLEANFILES=	${MAN}

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

${MAN}:
	sed -e 's,@''VERSION''@,${VERSION},g' \
	    -e 's,@''sbindir''@,/usr/sbin,g' \
	    -e 's,@''PATH_RADVD_CONF''@,${PATH_RADVD_CONF},g' \
	    -e 's,@''PATH_RADVD_PID''@,${PATH_RADVD_PID},g' \
	    -e 's,@''PATH_RADVD_LOG''@,${PATH_RADVD_LOG},g' \
	    -e 's,@''LOG_FACILITY''@,${LOG_FACILITY},g' \
	    ${DIST}/${.TARGET}.man > ${.TARGET}

.include <bsd.prog.mk>
