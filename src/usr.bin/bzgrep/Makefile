#	$ssdlinux: Makefile,v 1.1 2002/10/03 07:25:53 yamagata Exp $

.include <bsd.own.mk>

SCRIPTS=	bzgrep
SCRIPTSNAME=	${SCRIPTS}
MAN=		${SCRIPTS}.1

DIST=		${.CURDIR}/../../dist/bzip2
.PATH:		${DIST}

LINKS+=		${BINDIR}/${SCRIPTS}	${BINDIR}/bzegrep
LINKS+=		${BINDIR}/${SCRIPTS}	${BINDIR}/bzfgrep
SYMLINKS+=	${MANDIR}/man1/${MAN}	${MANDIR}/man1/bzegrep.1
SYMLINKS+=	${MANDIR}/man1/${MAN}	${MANDIR}/man1/bzfgrep.1

.include <bsd.prog.mk>
