#	$ssdlinux: Makefile,v 1.7 2004/06/15 14:42:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		useradd		
MAN=		${PROG}.8
CLEANFILES=	${MAN}

DIST=		${.CURDIR}/../../dist/shadow
.PATH:		${DIST}/src

USE_PAM=	no

.include "${.CURDIR}/../../lib/shadow/Makefile.cflags"
.include "${.CURDIR}/../../lib/shadow/Makefile.ldflags"
CPPFLAGS+=	-DUSER_DEFAULTS_FILE='"/etc/usermgmt.conf"'
CPPFLAGS+=	-DNEW_USER_FILE='"/etc/nuaddXXXXXX"'

NOGCCERROR=	yes

${MAN}:
	sed -e "s,/etc/default/useradd,/etc/usermgmt.conf,g" \
		${DIST}/man/${.TARGET} > ${.TARGET}.tmp
	mv ${.TARGET}.tmp ${.TARGET}

.include <bsd.prog.mk>
