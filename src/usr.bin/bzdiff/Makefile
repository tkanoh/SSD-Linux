#	$ssdlinux: Makefile,v 1.1 2002/10/03 07:25:53 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	bzdiff
SCRIPTSNAME=	${SCRIPTS}
MAN=		${SCRIPTS}.1

DIST=		${.CURDIR}/../../dist/bzip2
.PATH:		${DIST}

LINKS+=		${BINDIR}/${SCRIPTS}	${BINDIR}/bzcmp
SYMLINKS+=	${MANDIR}/man1/${MAN}	${MANDIR}/man1/bzcmp.1

.include <bsd.prog.mk>
