#	$ssdlinux: Makefile,v 1.1 2003/09/12 08:44:35 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	ntp-wait
CLEANFILES=	${SCRIPTS}

DIST=		${.CURDIR}/../../dist/ntpd
.PATH:		${DIST}/scripts

${SCRIPTS}: 
	sed -e 's,@PATH_PERL@,/usr/bin/perl,' \
		${DIST}/scripts/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
