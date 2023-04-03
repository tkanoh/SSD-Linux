#	$ssdlinux: Makefile,v 1.4 2003/06/03 05:17:09 yamagata Exp $
.include <bsd.own.mk>

PROG=		ngettext
MAN=		${PROG}.1
CLEANFILES=	${MAN}

CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
.include "${.CURDIR}/../Makefile.inc.grt"
.PATH:		${DIST}/gettext/gettext-runtime/src
CPPFLAGS+=	-I${.CURDIR}/../libgrt
CPPFLAGS+=	-I${DIST}/gettext/gettext-tools/lib

LIBDIR!=	cd ${.CURDIR}/../libgrt && ${PRINTOBJDIR}
LDADD+=		-L${LIBDIR} -lgrt
DPADD+=		${LIBDIR}/libgrt.a

${MAN}:
	sed -e 's,@localedir@,/usr/share/locale,' \
		${DIST}/gettext/gettext-runtime/man/${.TARGET}.in > ${.TARGET}

.include <bsd.prog.mk>
