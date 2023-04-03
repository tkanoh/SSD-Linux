#	$ssdlinux: Makefile,v 1.4 2005/02/09 05:40:03 todoroki Exp $

.include <bsd.own.mk>

WIRELESS=	ath_hal
MODULEOBJ=	hal.o
MKMAN=		no
CLEANFILES=	ah_osdep.c opt_ah.h

DIST=           ${.CURDIR}/../../../../../dist/madwifi/ath_hal

.include "../Makefile.cflags"

EXCPPFLAGS=	${CPPFLAGS} ${MFLAG} -DEXPORT_SYMTAB

ah_osdep.c:
	cp ${DIST}/../hal/linux/ah_osdep.c ah_osdep.c

opt_ah.h:
	cp ${DIST}/../hal/public/${TARGET}.opt_ah.h opt_ah.h

hal.o: ah_osdep.c opt_ah.h
	uudecode ${DIST}/../hal/public/${TARGET}.hal.o.uu

${SCRIPTS}: ${.TARGET:M*.o:.o=.c} ${MODULEOBJ}
	${CC} ${CPPFLAGS} ah_osdep.c
	${LD} -r -o .${.TARGET:M*.o.gz:.o.gz=.o} ah_osdep.o ${MODULEOBJ}
	mv .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o}
	${STRIP} -S ${.TARGET:M*.o.gz:.o.gz=.o}
	gzip -9 ${.TARGET:M*.o.gz:.o.gz=.o}

.include <bsd.prog.mk>
