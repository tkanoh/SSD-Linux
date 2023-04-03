#	$ssdlinux: Makefile,v 1.2 2002/10/03 07:16:00 yamagata Exp $

.include 	<bsd.own.mk>

PROG=		bzip2recover
MKMAN=		no

DIST=		${.CURDIR}/../../dist/bzip2
.PATH:		${DIST}

CPPFLAGS+=	-Wall -Winline -fomit-frame-pointer -fno-strength-reduce
CPPFLAGS+=	-D_FILE_OFFSET_BITS=64

.include <bsd.prog.mk>
