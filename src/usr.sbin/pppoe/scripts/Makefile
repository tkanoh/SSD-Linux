#	$ssdlinux: Makefile,v 1.3 2003/03/19 06:02:35 kuge Exp $

.include <bsd.own.mk>

SCRIPTS1=	adsl-connect adsl-init adsl-setup adsl-start adsl-stop
SCRIPTS2=	adsl-status
SCRIPTS=	${SCRIPTS1} ${SCRIPTS2}
MAN=		adsl-connect.8 adsl-setup.8 adsl-start.8 adsl-stop.8 adsl-status.8

${SCRIPTS1}:
	sed -e 's|@configure_input@|Generated by src/usr.sbin/pppoe/scripts/Makefile|g' \
	    -e 's|@prefix@|/usr|g' \
	    -e 's|@exec_prefix@|$$\{prefix\}|g' \
	    -e 's|@PPPD@|/usr/sbin/pppd|g' \
	    -e 's|@SETSID@|/usr/bin/setsid|g' \
	    -e 's|@sbindir@|$$\{exec_prefix\}/sbin|g' \
	    -e 's|@ID@|/usr/bin/id|g' \
	    -e 's|@ECHO@|/bin/echo|g' \
	    ${DIST}/scripts/${.TARGET}.in >> ${.TARGET}

${SCRIPTS2}:
	cp ${DIST}/scripts/${.TARGET} . 

CLEANFILES=	${SCRIPTS}

.include <bsd.prog.mk>
