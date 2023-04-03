#	$ssdlinux: Makefile,v 1.5 2004/06/23 05:53:11 yamagata Exp $

.include <bsd.own.mk>

LIBDHCPDIR=	${.CURDIR}/../../lib/dhcp
.include "${LIBDHCPDIR}/Makefile.cflags"

PROG=		dhcpd
SRCS=		${PROG}.c dhcp.c bootp.c confpars.c db.c class.c \
		failover.c omapi.c mdb.c stables.c salloc.c ddns.c
MAN=		${PROG}.8 ${PROG}.conf.5 ${PROG}.leases.5
CLEANFILES=	${MAN} ${PROG}.man8 ${PROG}.conf.man5 ${PROG}.leases.man5

DIST=		${.CURDIR}/../../dist/dhcp
.PATH:		${DIST}/server

CPPFLAGS+=	-I${DIST} -I${DIST}/includes

.include "${LIBDHCPDIR}/Makefile.ldflags"

${PROG}: ${PROG}.man8 ${PROG}.conf.man5 ${PROG}.leases.man5

${PROG}.man8:
	rm -f ${.TARGET}
	sed -e 's#ETCDIR#/etc#g' -e 's#DBDIR#/var/db#g' \
		-e 's#RUNDIR#/var/run#g' < ${DIST}/server/${PROG}.8 > ${.TARGET}
	cp ${PROG}.man8 ${PROG}.8

${PROG}.conf.man5:
	rm -f ${.TARGET}
	sed -e 's#ETCDIR#/etc#g' -e 's#DBDIR#/var/db#g' \
		-e 's#RUNDIR#/var/run#g' < ${DIST}/server/${PROG}.conf.5 > ${.TARGET}
	cp ${PROG}.conf.man5 ${PROG}.conf.5

${PROG}.leases.man5:
	rm -f ${.TARGET}
	sed -e 's#ETCDIR#/etc#g' -e 's#DBDIR#/var/db#g' \
		-e 's#RUNDIR#/var/run#g' < ${DIST}/server/${PROG}.leases.5 > ${.TARGET}
	cp ${PROG}.leases.man5 ${PROG}.leases.5

.include <bsd.prog.mk>
