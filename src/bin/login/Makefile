#	$ssdlinux: Makefile,v 1.3 2002/06/05 08:30:04 yamagata Exp $

.include <bsd.own.mk>

PROG=		login		

.if ${USE_PAM} == "yes"
LDSTATIC=
.endif

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src ${DIST}/man

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
