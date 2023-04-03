#	$ssdlinux: Makefile,v 1.3 2004/03/17 06:52:29 yamagata Exp $

.include <bsd.own.mk>

LIBDHCPDIR=	${.CURDIR}/../../lib/dhcp
.include "${LIBDHCPDIR}/Makefile.cflags"

PROG=		dhclient
SRCS=		dhclient.c clparse.c
SCRIPTS=	dhclient-script
SCRIPTSDIR=	/etc
SCRIPTSMODE=	700
MAN=		dhclient.8 dhclient.conf.5 dhclient-script.8 dhclient.leases.5
CLEANFILES=	dhclient-script ${MAN}

DIST=		${.CURDIR}/../../dist/dhcp
.PATH:		${DIST}/client

CPPFLAGS+=	-DCLIENT_PATH=${CLIENT_PATH} -I${DIST}/client -I${DIST}/includes
.include "${LIBDHCPDIR}/Makefile.ldflags"

dhclient-script:
	sed -e 's/^function //' < ${DIST}/client/scripts/linux > ${.CURDIR}/dhclient-script
	for i in ${MAN}; \
	do \
		sed -e 's#ETCDIR#/etc#g' -e 's#DBDIR#/var/db#g' \
	    	    -e 's#CLIENTBINDIR#/etc#g' \
            	    -e 's#RUNDIR#/var/run#g' < ${DIST}/client/$$i > $$i ; \
	done

.include <bsd.prog.mk>
