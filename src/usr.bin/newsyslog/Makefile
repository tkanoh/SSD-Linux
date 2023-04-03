#	$ssdlinux: Makefile,v 1.5 2004/08/30 09:37:33 yamagata Exp $

.include <bsd.own.mk>

PROG=		newsyslog
SRCS=		${PROG}.c sig2str.c str2sig.c sys_signame.c
MAN=		${PROG}.8 ${PROG}.conf.5
CLEANFILES=	sys_signame.c

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-DHAVE_CONFIG_H

sys_signame.c:
	${SHELL} ${DIST}/mksigname.sh ${DIST}/siglist.in ${.TARGET}

NOGCCERROR=	yes

.include <bsd.prog.mk>
