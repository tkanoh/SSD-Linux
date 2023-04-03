#	$ssdlinux: Makefile,v 1.2 2003/01/06 02:35:18 kanoh Exp $

.include <bsd.own.mk>

PROG=		radvd
SRCS=		radvd.c timer.c send.c process.c interface.c device.c \
		device-common.c gram.c scanner.c
MAN=		${PROG}.8 ${PROG}.conf.5
CLEANFILES=	device.c ${MAN}

.include "${.CURDIR}/../Makefile.cflags"
.include "${.CURDIR}/../Makefile.ldflags"

LDADD+=		-L${.CURDIR}/../../../lib/libfl -lfl

device.c: device-linux.c
	ln -s ${DIST}/device-linux.c ${.TARGET}

${MAN}:
	sed -e 's,@''VERSION''@,${VERSION},g' \
	    -e 's,@''sbindir''@,/usr/sbin,g' \
	    -e 's,@''PATH_RADVD_CONF''@,${PATH_RADVD_CONF},g' \
	    -e 's,@''PATH_RADVD_PID''@,${PATH_RADVD_PID},g' \
	    -e 's,@''PATH_RADVD_LOG''@,${PATH_RADVD_LOG},g' \
	    -e 's,@''LOG_FACILITY''@,${LOG_FACILITY},g' \
	    ${DIST}/${.TARGET}.man > ${.TARGET}

.include <bsd.prog.mk>
