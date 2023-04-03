#	$ssdlinux: Makefile,v 1.8 2005/03/02 05:59:36 yamagata Exp $

.include <bsd.own.mk>

LIB=		e2p
SRCS=		feature.c fgetflags.c fsetflags.c fgetversion.c fsetversion.c \
		getflags.c getversion.c hashstr.c iod.c ls.c mntopts.c \
		parse_num.c pe.c pf.c ps.c setflags.c setversion.c uuid.c
MKPIC=		yes
MKPICINSTALL=	no
MKMAN=		no

FILES=		e2p.h
FILESMODE=	444
FILESDIR=	/usr/include/${LIB}

DIST=		${.CURDIR}/../../../dist/e2fsprogs
.PATH:		${DIST}/lib/${LIB}

.include "${.CURDIR}/../Makefile.cflags"

.include <bsd.lib.mk>
