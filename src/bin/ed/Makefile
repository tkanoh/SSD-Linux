#	$ssdlinux: Makefile,v 1.3 2002/06/05 08:23:21 yamagata Exp $

.include <bsd.own.mk>

PROG=		ed		
SRCS=		buf.c glbl.c io.c main.c re.c signal.c sub.c undo.c version.c \
		getopt.c getopt1.c regex.c

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST}

CPPFLAGS+=	-I${.CURDIR} -I${DIST} -DHAVE_CONFIG_H

SYMLINKS+=      ${BINDIR}/${PROG} ${BINDIR}/red
MLINKS+=	${PROG}.1 red.1


.include <bsd.prog.mk>
