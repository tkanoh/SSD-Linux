#	$ssdlinux: Makefile,v 1.1.1.1 2002/05/02 13:37:09 kanoh Exp $

# IF YOU ADD TO MSRCS, MAKE SURE YOU UPDATE `CATDEPS' IN bsd.man.mk!
MSRCS=  andoc doc doc-ditroff doc-common doc-nroff doc-syms doc2html
MMACS=  ${MSRCS:S@^@tmac.@g}
INCS=	${MMACS}
INCSDIR=${BINDIR}/tmac
LINKS=	${INCSDIR}/tmac.andoc ${INCSDIR}/tmac.an
FILESDIR= /usr/share/tmac
FILES=	tmac.andoc
CLEANFILES+= ${MMACS}

TMACDIR?=${.CURDIR}
STRIP_SED = ${TMACDIR}/../me/strip.sed

# old macros not currently installed...
OFILES=	tmac.an.v6compat tmac.an6n tmac.an6t tmac.a tmac.cp tmac.doc.old

realall:	${MMACS}

.for i in ${MSRCS}
tmac.$i: $i
	sed -f ${STRIP_SED} < ${.ALLSRC} > ${.TARGET}
.endfor

.include <bsd.prog.mk>
