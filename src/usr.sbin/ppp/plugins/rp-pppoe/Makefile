#	$ssdlinux: Makefile,v 1.3 2004/11/15 06:03:10 yamagata Exp $

.include <bsd.own.mk>

PROG=		pppoe-discovery
PLUGINS=	rp-pppoe.so
LIBPLUGIN=	libplugin.a
OBJS=		discovery.o if.o common.o debug.o
LIBDIR=		/usr/libexec/ppp

DIST=		${.CURDIR}/../../../../dist/ppp/pppd/plugins/rp-pppoe
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST}/../../../include/linux

.MAIN: all
all: ${PLUGINS} ${PROG}

${PROG}: ${LIBPLUGIN} ${PROG}.o 
	${CC} -o ${.TARGET} ${PROG}.o ${LIBPLUGIN}

pppoe-discovery.o:
	${CC} ${CPPFLAGS} '-DVERSION="3.3"' -c -o ${.TARGET} ${DIST}/${.TARGET:.o=.c}

${PLUGINS}: ${LIBPLUGIN} plugin.o
	${CC} -o ${.TARGET} -shared plugin.o ${LIBPLUGIN}

plugin.o:
	${CC} '-DRP_VERSION="3.3"' ${CPPFLAGS} -I${DIST}/../../.. -c -o ${.TARGET} -fPIC ${DIST}/${.TARGET:.o=.c}

${LIBPLUGIN}: ${OBJS}
	${AR} -rc ${.TARGET} ${OBJS}
	
${OBJS}:
	${CC} ${CPPFLAGS} '-DVERSION="3.3"' -c -o ${.TARGET} -fPIC ${DIST}/${.TARGET:.o=.c}

install:
	${INSTALL} -c -m ${LIBMODE} -g ${LIBGRP} -o ${LIBOWN} ${PLUGINS} ${DESTDIR}${LIBDIR}
	${INSTALL} -c -m ${BINMODE} -g ${BINGRP} -o ${BINOWN} ${PROG} ${DESTDIR}/usr/sbin

clean:
	rm -f ${PLUGINS} ${PROG} ${LIBPLUGIN} ${OBJS} *.o

cleandir:
