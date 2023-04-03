#	$ssdlinux: Makefile,v 1.7 2004/04/08 06:16:47 todoroki Exp $

.include <bsd.own.mk>

WIRELESS=	wvlan_cs
MODULEOBJ=	wvlan_hcf.o wvlan_hcfio.o
MAN=		wvlan_cs.4
ALTMKSCRIPTS=	yes

.include "../Makefile.cflags"

EXCPPFLAGS=	${CPPFLAGS} ${MFLAG} -DEXPORT_SYMTAB

${MODULEOBJ}:
	${CC} ${EXCPPFLAGS} ${DIST}/${DISTSUBDIR}/${.TARGET:M*.o:.o=.c}

${SCRIPTS}: ${.TARGET:M*.o:.o=.c} ${MODULEOBJ}
	${CC} ${CPPFLAGS} ${DIST}/${DISTSUBDIR}/wvlan_base.c
	${LD} -r -o .${.TARGET:M*.o.gz:.o.gz=.o} wvlan_base.o ${MODULEOBJ}
	mv .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o}
	gzip -9 ${.TARGET:M*.o.gz:.o.gz=.o}

.include <bsd.prog.mk>
