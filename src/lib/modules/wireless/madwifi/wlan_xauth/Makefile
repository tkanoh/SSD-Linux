#	$ssdlinux: Makefile,v 1.2 2004/08/27 07:01:31 todoroki Exp $

.include <bsd.own.mk>

WIRELESS=	wlan_xauth
MKMAN=		no

DIST=           ${.CURDIR}/../../../../../dist/madwifi/net80211

.include "../Makefile.cflags"

EXCPPFLAGS=	${CPPFLAGS} ${MFLAG} -DEXPORT_SYMTAB


${SCRIPTS}: ${.TARGET:M*.o:.o=.c}
	${CC} ${CPPFLAGS} ${DIST}/${DISTSUBDIR}/ieee80211_xauth.c
	${LD} -r -o .${.TARGET:M*.o.gz:.o.gz=.o} ieee80211_xauth.o
	mv .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o}
	${STRIP} -S ${.TARGET:M*.o.gz:.o.gz=.o}
	gzip -9 ${.TARGET:M*.o.gz:.o.gz=.o}

.include <bsd.prog.mk>
