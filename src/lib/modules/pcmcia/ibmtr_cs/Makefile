#	$ssdlinux: Makefile,v 1.3 2004/04/08 06:16:47 todoroki Exp $

.include <bsd.own.mk>
.include "../Makefile.inc"

SCRIPTS=	ibmtr_cs.o.gz
MODULEOBJ=	ibmtr.o
MAN=		ibmtr_cs.4
CLEANFILES=	${SCRIPTS} *.o *.d

DIST=		${DISTDIR}/clients
DRIVERS=	${KERNSRC}/drivers/net/tokenring
.PATH:		${DIST} ${DISTDIR}/man ${DRIVERS}

CPPFLAGS=	-MD -c -O2 $(INCLUDES)
CPPFLAGS+=	-D__KERNEL__ -DMODULE -DEXPORT_SYMTAB -DMODVERSIONS -DPCMCIA -D__NO_VERSION__

CPPFLAGS1=	-MD -c -O3 -Wstrict-prototypes -pipe $(INCLUDES)
CPPFLAGS1+=	-D__KERNEL__ -DMODULE

${MODULEOBJ}: ${.TARGET:M*.o:.o=.c}
	${CC} $(CPPFLAGS) ${DRIVERS}/${.TARGET:M*.o:.o=.c}

${SCRIPTS}: ${.TARGET:M*.o.gz:.o.gz=.c} ${MODULEOBJ}
	${CC} $(CPPFLAGS1) ${DIST}/${.TARGET:M*.o.gz:.o.gz=.c}
	${LD} -r -o .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o} ${MODULEOBJ}
	mv .${.TARGET:M*.o.gz:.o.gz=.o} ${.TARGET:M*.o.gz:.o.gz=.o}
	gzip -9 ${.TARGET:M*.o.gz:.o.gz=.o}

scriptsinstall::
	${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${SCRIPTS} $(DESTDIR)$(BINDIR)

.include <bsd.prog.mk>
