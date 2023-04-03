#	$ssdlinux: Makefile,v 1.2 2002/06/12 00:56:29 yamagata Exp $

.include <bsd.own.mk>

PROG=		gzip
SRCS=		minigzip.c
MKMAN=		no
	
DIST=	   	${.CURDIR}/../../../dist/zlib
.PATH:	   	${DIST}

CPPFLAGS+=	-DHAVE_UNISTD_H -DUSE_MMAP
CPPFLAGS+=	-I${DIST}

LDADD+=		-L${.CURDIR}/../../../lib/libz -lz
DPADD+=		${.CURDIR}/../../../lib/libz/libz.a

proginstall:

.include <bsd.prog.mk>
