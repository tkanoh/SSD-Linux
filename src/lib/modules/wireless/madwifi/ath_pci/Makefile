#	$ssdlinux: Makefile,v 1.3 2004/08/27 07:01:31 todoroki Exp $

.include <bsd.own.mk>

WIRELESS=	ath_pci
MODULEOBJ=	if_ath.o
MKMAN=		no

DIST=           ${.CURDIR}/../../../../../dist/madwifi/ath

.include "../Makefile.cflags"

EXCPPFLAGS=	${CPPFLAGS} ${MFLAG} -DEXPORT_SYMTAB

${MODULEOBJ}:
	${CC} ${EXCPPFLAGS} ${DIST}/${DISTSUBDIR}/${.TARGET:M*.o:.o=.c}

${SCRIPTS}: ${.TARGET:M*.o:.o=.c} ${MODULEOBJ}
	${CC} ${CPPFLAGS} ${DIST}/${DISTSUBDIR}/if_ath_pci.c
	${LD} -r -o .${.TARGET:M*.o.gz:.o.gz=.o} if_ath_pci.o ${MODULEOBJ}
	mv .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o}
	${STRIP} -S ${.TARGET:M*.o.gz:.o.gz=.o}
	gzip -9 ${.TARGET:M*.o.gz:.o.gz=.o}

.include <bsd.prog.mk>
