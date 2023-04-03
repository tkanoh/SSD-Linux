#	$ssdlinux: Makefile,v 1.7 2004/11/15 06:01:01 yamagata Exp $

.include <bsd.own.mk>

PROG=		pppd
SRCS=		main.c magic.c fsm.c lcp.c ipcp.c upap.c chap-new.c md5.c ccp.c \
		ecp.c ipxcp.c auth.c options.c sys-linux.c md4.c chap_ms.c \
		demand.c utils.c eap.c tty.c chap-md5.c
SRCS+=		sha1.c
# -DUSE_CRYPT=1
SRCS+=		pppcrypt.c
# -DHAVE_MULTILINK
SRCS+=		multilink.c
# -DUSE_TDB=1
SRCS+=		tdb.c spinlock.c
MAN=		${PROG}.8

CPPFLAGS=	-pipe -Wall
CPPFLAGS+=	-DHAVE_PATHS_H -DIPX_CHANGE -DHAVE_MMAP
CPPFLAGS+=	-I${DIST}/include
CPPFLAGS+=	-DCHAPMS=1 -DMPPE=1
CPPFLAGS+=	-DHAS_SHADOW
CPPFLAGS+=	-DHAVE_CRYPT_H=1
CPPFLAGS+=	-DUSE_CRYPT=1
CPPFLAGS+=	-DHAVE_MULTILINK
CPPFLAGS+=	-DUSE_TDB=1
CPPFLAGS+=	-DPLUGIN
CPPFLAGS+=	-DMAXOCTETS

LDADD+=		-lcrypt -ldl

LDFLAGS+= 	-Wl,-E		#20030509 PLATC2,INC.

NOGCCERROR=	yes

.include <bsd.prog.mk>
