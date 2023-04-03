#	$ssdlinux: Makefile,v 1.1 2004/11/09 02:10:45 todoroki Exp $

.include <bsd.own.mk>

WIRELESS=	ath_rate_onoe
MKMAN=		no

DIST=           ${.CURDIR}/../../../../../dist/madwifi/ath_rate/onoe

.include "./Makefile.cflags"

EXCPPFLAGS=	${CPPFLAGS} ${MFLAG} -DEXPORT_SYMTAB


${SCRIPTS}: ${.TARGET:M*.o:.o=.c}
	${CC} ${CPPFLAGS} ${DIST}/${DISTSUBDIR}/onoe.c
	${LD} -r -o .${.TARGET:M*.o.gz:.o.gz=.o} onoe.o
	mv .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o}
	${STRIP} -S ${.TARGET:M*.o.gz:.o.gz=.o}
	gzip -9 ${.TARGET:M*.o.gz:.o.gz=.o}

.include <bsd.prog.mk>
