#	$ssdlinux: Makefile,v 1.5 2004/07/03 13:04:28 yamagata Exp $

.include <bsd.own.mk>

PROG=		rexecd
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-rsh/${PROG}
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

CPPFLAGS+=	-I${.CURDIR}/../../bin/rcp
CPPFLAGS+=	-DHAVE_LIBCRYPT=1 -DHAVE_LOGWTMP=1
CPPFLAGS+=	-DHAVE_SHADOW_H=1

LDADD+=		 -lutil -lcrypt
.if ${USE_PAM} == "yes"
CPPFLAGS+=	-DUSE_PAM=1 -DHAVE_SECURITY_PAM_APPL_H=1
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+= -I${DIST}/../../../../../lib/pam/include
CPPFLAGS+= -I${DIST}/../../../../Linux-PAM/libpam/include
CPPFLAGS+= -I${DIST}/../../../../Linux-PAM/libpamc/include
CPPFLAGS+= -I${DIST}/../../../../Linux-PAM/libpam_misc/include
.endif
LDADD+=		-L${.CURDIR}/../../lib/pam/libpam -lpam
DPADD+=		${.CURDIR}/../../lib/pam/libpam/libpam.a
.endif

.include <bsd.prog.mk>
