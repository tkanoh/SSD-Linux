#	$ssdlinux: Makefile,v 1.3 2002/12/26 14:18:56 kanoh Exp $

.include <bsd.own.mk>

SCRIPTS=	3CCFEM556.dat 3CXEM556.dat COMpad2.dat COMpad4.dat \
		DP83903.dat E-CARD.dat LA-PCM.dat MT5634ZLX.dat \
		NE2K.dat PCMLM28.dat PE-200.dat PE520.dat RS-COM-2P.dat \
		tamarack.dat
SCRIPTSDIR=	/etc/pcmcia/cis
SCRIPTSMODE=	444
CLEANFILES=	${SCRIPTS}

DIST=		${.CURDIR}/../../../dist/pcmcia-cs/etc/cis
.PATH:		${DIST}

.if ${MACHINE_ARCH} == ${TARGET_HOSTTYPE}
${SCRIPTS}::
	/usr/bin/pack_cis -o `basename ${.TARGET}` ${.TARGET:M*.dat:.dat=.cis}
.else
${SCRIPTS}: ${.TARGET:M*.dat:.dat=.cis}
	/usr/bin/pack_cis -o `basename ${.TARGET}` ${.TARGET:M*.dat:.dat=.cis}
.endif

scriptsinstall::
	${INSTALL} -c -m ${SCRIPTSMODE} -o ${BINOWN} -g ${BINGRP} ${SCRIPTS} ${DESTDIR}${SCRIPTSDIR}

.include <bsd.prog.mk>
