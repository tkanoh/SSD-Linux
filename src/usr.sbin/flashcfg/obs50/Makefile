#	$ssdlinux: Makefile,v 1.1 2003/04/05 07:45:31 kanoh Exp $
#
# binary distribution only for license isseu.

.include <bsd.own.mk>
.include "../Makefile.inc"

PROG=		flashcfg		

.MAIN: all
all:
	uudecode ${PROG}.uu

install:
	${INSTALL} -c -m ${BINMODE} -o ${BINOWN} -g ${BINGRP} ${PROG} ${DESTDIR}${BINDIR}/${PROG}

clean:
	rm -f ${PROG}

cleandir:
