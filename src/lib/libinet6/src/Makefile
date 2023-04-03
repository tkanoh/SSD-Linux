#	$ssdlinux: Makefile,v 1.7 2004/08/07 06:22:16 kanoh Exp $

.include 	<bsd.own.mk>

LIB=		inet6
SRCS=		usagi.c getaddrinfo.c getnameinfo.c ip6opt.c rthdr.c \
		ifaddrs.c ifnames.c cmsg_nxthdr.c rcmd.c rexec.c \
		sa_len.c tempname.c
MKPIC=		yes
MKPICINSTALL=	no
MAN=		getifaddrs.3

.if ${GLIBC_VERSION} == "2.3.2" || ${GLIBC_VERSION} == "2.3.3"
CPPFLAGS+=	-D_LIBC_REENTRANT -D_IO_MTSAFE_IO
.else
CPPFLAGS+=	-D_LIBC
.endif
CPPFLAGS+=	-D_USAGI -D_GNU_SOURCE -DCOMPAT_RFC2292
.if ${GLIBC_MAJOR_VERSION} == "2.3"
CPPFLAGS+=	-D_USAGI_LIBINET6=23
.else
CPPFLAGS+=	-D_USAGI_LIBINET6=22
.endif
CPPFLAGS+=	-I${.CURDIR}/../include -I${DIST}
CPPFLAGS+=	-D__ss_family=ss_family -D__ss_len=ss_len

.include	"../Makefile.inc"

.PATH:		${DIST}

NOGCCERROR=	yes

.include <bsd.lib.mk>
