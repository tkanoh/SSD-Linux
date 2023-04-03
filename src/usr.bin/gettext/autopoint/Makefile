#	$ssdlinux: Makefile,v 1.6 2005/03/15 02:31:24 yamagata Exp $

SCRIPTS=	autopoint
CLEANFILES=	${SCRIPTS}

.include "${.CURDIR}/../Makefile.inc.prog"
.include "${.CURDIR}/../Makefile.inc.tools"

${SCRIPTS}:
	rm -f ${.TARGET}
	sed -e 's,@PACKAGE@,gettext-tools,' \
	    -e 's,@VERSION@,0.14.3,' \
	    -e 's,@prefix@,/usr,' \
	    -e 's,@datadir@,$${prefix}/share,g' \
	    -e 's,@RELOCATABLE@,no,' \
	    -e 's,@exec_prefix@,$${prefix},' \
	    -e 's,@bindir@,$${exec_prefix}/bin,' \
		${DIST}/gettext/gettext-tools/misc/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
