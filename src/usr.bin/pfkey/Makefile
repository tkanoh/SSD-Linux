#	$ssdlinux: Makefile,v 1.1.1.1 2002/05/02 13:37:11 kanoh Exp $

.include 	<bsd.own.mk>

PROG=		pfkey
SRCS=		pfkey.c pfkeylib.c pfkey_v2_build.c pfkey_v2_ext_bits.c pfkey_v2_parse.c
SCRIPTS=	ipsec-set
FILES=		ipsec-static.conf
FILESDIR=	/etc
MKMAN=		no

DIST=		${.CURDIR}/../../dist/usagi-tool/usagi/pfkey_util
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST} -I${.CURDIR}/../../linux/include

NOGCCERROR=	yes

.include <bsd.prog.mk>
