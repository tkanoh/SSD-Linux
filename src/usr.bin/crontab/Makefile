#	$ssdlinux: Makefile,v 1.6 2003/09/05 06:13:40 yamagata Exp $

.include <bsd.own.mk>

PROG=		crontab
SRCS=		${PROG}.c misc.c entry.c env.c compat.c
MAN=		${PROG}.1 ${PROG}.5
.if defined(DESTDIR) || !make(install)
FILESDIR=	/var/cron/tabs
FILESMODE=	600
FILES=		root
.endif

DIST=		${.CURDIR}/../../dist/cron
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR} -I${DIST}

.include <bsd.prog.mk>
