#	$ssdlinux: Makefile,v 1.8 2004/11/15 06:02:04 yamagata Exp $

.include <bsd.own.mk>
.include "${.CURDIR}/../Makefile.inc"

PLUGINS=	minconn.so passprompt.so passwordfd.so winbind.so
LIBDIR=		/usr/libexec/ppp

PLUGINS_DIST=	${DIST}/pppd/plugins
.PATH:		${PLUGINS_DIST}

CPPFLAGS=	-shared -O2 -g
CPPFLAGS+=	-I${PLUGINS_DIST}/.. -I${PLUGINS_DIST}/../../include
CPPFLAGS+=	-fPIC

.MAIN: all
all: ${PLUGINS}

${PLUGINS}:
	${CC} -o ${.TARGET} ${CPPFLAGS} ${PLUGINS_DIST}/${.TARGET:.so=.c}

install:
	${INSTALL} -c -m ${LIBMODE} -g ${LIBGRP} -o ${LIBOWN} ${PLUGINS} ${DESTDIR}${LIBDIR}

clean:
	rm -f ${PLUGINS}

cleandir:

SUBDIR=		rp-pppoe pppoatm radius 

.include <bsd.subdir.mk>
