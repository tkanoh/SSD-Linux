#	$ssdlinux: Makefile,v 1.9 2004/06/04 03:58:43 yamagata Exp $

.include <bsd.own.mk>

PROG=		make
REMOTE=		stub
SRCS=		ar.c arscan.c commands.c default.c dir.c expand.c file.c \
		function.c getopt.c getopt1.c implicit.c job.c main.c \
		misc.c read.c remake.c remote-${REMOTE}.c rule.c signame.c \
		variable.c version.c vpath.c hash.c

FILES=		make.info make.info-1 make.info-2 make.info-3 make.info-4 \
		make.info-5 make.info-6 make.info-7 make.info-8 make.info-9 \
		make.info-10 make.info-11
FILESDIR=	/usr/share/info

BINGRP=		kmem
BINMODE=	2755

DIST=		${.CURDIR}/../../dist/${PROG}
.PATH:		${DIST} ${DIST}/doc

CPPFLAGS=	-DLOCALEDIR=\"/usr/share/locale\"
CPPFLAGS+=	-DLIBDIR=\"/usr/lib\"
CPPFLAGS+=	-DINCLUDEDIR=\"/usr/include\"
CPPFLAGS+=	-DHAVE_CONFIG_H
.if ${TARGET_HOSTTYPE} == "i386"
CPPFLAGS+=	-DMAKE_HOST='"i386-ssd-linux-gnu"'
.elif ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DMAKE_HOST='"powerpc-ssd-linux-gnu"'
.endif
CPPFLAGS+=	-I${.CURDIR}
CPPFLAGS+=	-I${DIST}

LDADD=		-lutil -lrt

install:
	install-info ${DESTDIR}${FILESDIR}/${PROG}.info ${DESTDIR}${FILESDIR}/dir

.include <bsd.prog.mk>
