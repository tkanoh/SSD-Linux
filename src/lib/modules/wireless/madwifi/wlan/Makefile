#	$ssdlinux: Makefile,v 1.3 2004/08/27 07:01:31 todoroki Exp $

.include <bsd.own.mk>

WIRELESS=	wlan
MODULEOBJ=	if_media.o ieee80211.o ieee80211_crypto.o ieee80211_input.o \
		ieee80211_node.o ieee80211_output.o ieee80211_proto.o \
		ieee80211_wireless.o ieee80211_linux.o ieee80211_crypto_none.o
MKMAN=		no

DIST=           ${.CURDIR}/../../../../../dist/madwifi/net80211

.include "../Makefile.cflags"

EXCPPFLAGS=	${CPPFLAGS} ${MFLAG} -DEXPORT_SYMTAB

${MODULEOBJ}:
	${CC} ${EXCPPFLAGS} ${DIST}/${DISTSUBDIR}/${.TARGET:M*.o:.o=.c}

${SCRIPTS}: ${.TARGET:M*.o:.o=.c} ${MODULEOBJ}
	${CC} ${CPPFLAGS} ${DIST}/${DISTSUBDIR}/rc4.c
	${LD} -r -o .${.TARGET:M*.o.gz:.o.gz=.o} rc4.o ${MODULEOBJ}
	mv .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o}
	${STRIP} -S ${.TARGET:M*.o.gz:.o.gz=.o}
	gzip -9 ${.TARGET:M*.o.gz:.o.gz=.o}

.include <bsd.prog.mk>
