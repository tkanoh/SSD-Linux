#	$ssdlinux: Makefile,v 1.4 2004/05/31 07:01:42 yamagata Exp $

.include <bsd.own.mk>

MODULE=		pam_limits
CONFFILE=	limits.conf
MAKECONF=	cp ${MSRCDIR}/${MODULE}/limits.skel ${CONFFILE}
CLEANFILES+=	${CONFFILE}

.include "${.CURDIR}/../Makefile.cflags"

.include <bsd.prog.mk>
