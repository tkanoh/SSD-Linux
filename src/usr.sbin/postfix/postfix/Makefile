#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:08:51 yamagata Exp $

.include <bsd.own.mk>

PROG=		postfix
MAN=		${PROG}.1
MAN+=		access.5 aliases.5 canonical.5 pcre_table.5 \
		regexp_table.5 relocated.5 transport.5 virtual.5

DIST=		${.CURDIR}/../../../dist/postfix
.PATH:		${DIST}/src/${PROG} ${DIST}/man/man1 ${DIST}/man/man5

.include <bsd.prog.mk>
