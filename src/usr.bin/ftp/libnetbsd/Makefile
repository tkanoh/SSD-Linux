#	$ssdlinux: Makefile,v 1.2 2004/07/04 05:52:11 yamagata Exp $

.include <bsd.own.mk>

LIB=		netbsd
SRCS=		fgetln.c setprogname.c sl_init.c strlcat.c strlcpy.c \
		strunvis.c strvis.c fparseln.c glob.c

DIST=		${.CURDIR}/../../../dist/tnftp
.PATH:		${DIST}/libnetbsd

.if ${IPV6} == "yes"
CPPFLAGS+=	-DHAVE_AF_INET6=1
CPPFLAGS+=	-DHAVE_SOCKADDR_IN6=1
CPPFLAGS+=	-DHAVE_IN6ADDRSZ=1
.endif
CPPFLAGS+=	-I${DIST}/libnetbsd -I${DIST} -I${.CURDIR}/.. -I${DIST}/libedit
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../termcap
.endif
LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
