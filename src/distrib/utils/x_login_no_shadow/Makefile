#	$ssdlinux: Makefile,v 1.3 2002/08/05 04:06:57 yamagata Exp $

.include <bsd.own.mk>

PROG=		login
SRCS=		${PROG}.c checktty.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/util-linux
.PATH:		${DIST}/login-utils

LIBULDIR=      ${.CURDIR}/../../../lib/util-linux
.include "${LIBULDIR}/Makefile.cflags"
CPPFLAGS+=	-I${.CURDIR} -I${DIST}/login-utils -I${DIST}/lib -I${LIBULDIR}/dummy

LDADD+=		-L${LIBULDIR} -lutil-linux -lcrypt
DPADD+=		${LIBULDIR}/libutil-linux.a

CPPFLAGS+=	-DUSE_TTY_GROUP -DCHOWNVCS

proginstall::

.ifdef		USE_PAM
.undef		USE_PAM
.endif

.ifdef		SHADOW_PWD
.undef		SHADOW_PWD
.endif

.include <bsd.prog.mk>
