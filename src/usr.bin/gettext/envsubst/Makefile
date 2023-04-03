#	$ssdlinux: Makefile,v 1.1 2003/12/15 03:44:03 yamagata Exp $
.include <bsd.own.mk>

PROG=		envsubst

CPPFLAGS+=	-DLOCALEDIR=\"/usr/share/locale\"
.include "${.CURDIR}/../Makefile.inc.grt"
.PATH:          ${DIST}/gettext/gettext-runtime/src ${DIST}/gettext/gettext-runtime/man
CPPFLAGS+=	-I${.CURDIR}/../libgrt
CPPFLAGS+=	-I${DIST}/gettext/gettext-tools/lib

LIBDIR!=	cd ${.CURDIR}/../libgrt && ${PRINTOBJDIR}
LDADD+=		-L${LIBDIR} -lgrt
DPADD+=		${LIBDIR}/libgrt.a

.include <bsd.prog.mk>
