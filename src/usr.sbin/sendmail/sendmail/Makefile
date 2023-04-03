#	$ssdlinux: Makefile,v 1.6 2004/09/03 06:31:47 yamagata Exp $

.include <bsd.own.mk>

PROG=		sendmail
SRCS=		main.c alias.c arpadate.c bf.c collect.c conf.c control.c \
		convtime.c daemon.c deliver.c domain.c envelope.c err.c \
		headers.c macro.c map.c mci.c milter.c mime.c parseaddr.c \
		queue.c ratectrl.c readcf.c recipient.c savemail.c sasl.c sfsasl.c \
		shmticklib.c sm_resolve.c srvrsmtp.c stab.c stats.c \
		sysexits.c timers.c tls.c trace.c udb.c usersmtp.c util.c \
		version.c
BINOWN=		root
BINGRP=		smmsp
BINMODE=	2555
SCRIPTS=	statistics			
SCRIPTSDIR=	/etc/mail
SCRIPTSMODE=	644
SCRIPTSOWN=	root
SCRIPTSGRP=	bin
FILES=		helpfile
FILESDIR=	${SCRIPTSDIR}
FILESMODE=	444
FILESOWN=	root
FILESGRP=	bin
MAN=		${PROG}.8 aliases.5 mailq.1 newaliases.1

DIST=		${.CURDIR}/../../../dist/sendmail
.PATH:		${DIST}/${PROG}

CPPFLAGS+=	-I${DIST}/${PROG}
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../../lib/libdb
.endif

LINKS+=		${BINDIR}/${PROG} /usr/bin/mailq
LINKS+=		${BINDIR}/${PROG} /usr/bin/newaliases
LINKS+=		${BINDIR}/${PROG} /usr/bin/hoststat
LINKS+=		${BINDIR}/${PROG} /usr/bin/purgestat

CLEANFILES=	${SCRIPTS}

${SCRIPTS}:
	touch ${.TARGET}

.include <bsd.prog.mk>
