#	$ssdlinux: Makefile,v 1.5 2004/07/04 07:06:22 yamagata Exp $

.include <bsd.own.mk>

PROG=		inetd
MAN=		${PROG}.8
MLINKS=		${PROG}.8 ${PROG}.conf.5

CPPFLAGS+=	-DLIBWRAP
# Use LIBWRAP_INTERNAL for libwrap checking of inetd's `internal' services.
#CPPFLAGS+=	-DLIBWRAP_INTERNAL
LDADD+=		-L${.CURDIR}/../../lib/libwrap -lwrap
DPADD+=		${.CURDIR}/../../lib/libwrap/libwrap.a

# This is necessary due to be friendly with past API changes... DAMN.
CPPFLAGS+=	-Dss_family=__ss_family -Dss_len=__ss_len
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../dist/usagi-tool/src/tcp_wrappers
.endif

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"
.include "${LIBINET6}/Makefile.ldflags"

.include <bsd.prog.mk>
