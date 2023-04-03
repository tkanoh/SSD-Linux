#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:08:51 yamagata Exp $

.include <bsd.own.mk>

PROG=		sendmail
MAN=		${PROG}.1 mailq.1 newaliases.1

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man1

SYMLINKS+=	${BINDIR}/${PROG} /usr/bin/mailq
SYMLINKS+=	${BINDIR}/${PROG} /usr/bin/newaliases

.include <bsd.prog.mk>
