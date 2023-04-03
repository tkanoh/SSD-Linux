#	$ssdlinux: Makefile,v 1.6 2005/03/15 02:31:02 yamagata Exp $
.include <bsd.own.mk>

PROG=		gettext
MAN=		${PROG}.1
SCRIPTS=	${PROG}.sh
SCRIPTSNAME=	${PROG}.sh
CLEANFILES=	${MAN} ${SCRIPTS}

CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
.include "${.CURDIR}/../Makefile.inc.grt"
.PATH:          ${DIST}/gettext/gettext-runtime/src
CPPFLAGS+=	-I${.CURDIR}/../libgrt
CPPFLAGS+=	-I${DIST}/gettext/gettext-tools/lib

LIBDIR!=	cd ${.CURDIR}/../libgrt && ${PRINTOBJDIR}
LDADD+=		-L${LIBDIR} -lgrt
DPADD+=		${LIBDIR}/libgrt.a

${SCRIPTS}:
	sed -e "s/@PACKAGE@/gettext-runtime/" \
	    -e "s/@VERSION@/0.14.3/" \
	${DIST}/gettext/gettext-runtime/src/${.TARGET}.in > ${.TARGET}

${MAN}:
	sed -e 's,@localedir@,/usr/share/locale,' \
		${DIST}/gettext/gettext-runtime/man/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
