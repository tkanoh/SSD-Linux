#	$ssdlinux: Makefile,v 1.1 2004/02/12 08:20:42 yamagata Exp $

.include <bsd.own.mk>

LIB=		netbsd
SRCS=		fgetln.c inet_net_pton.c sl_init.c strsuftollx.c strlcat.c \
		strlcpy.c fparseln.c glob.c fnmatch.c strmode.c user_from_uid.c

DIST=		${.CURDIR}/../../../dist/tnftpd
.PATH:		${DIST}/libnetbsd

.if ${IPV6} == "yes
CPPFLAGS+=	-DHAVE_AF_INET6=1
CPPFLAGS+=	-DHAVE_SOCKADDR_IN6=1
.endif
CPPFLAGS+=	-I${DIST}/libnetbsd -I${DIST} -I${DIST}/src -I${.CURDIR}/..
LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

NOGCCERROR=	yes

libinstall::

.include <bsd.lib.mk>
