#	$ssdlinux: Makefile,v 1.1 2004/11/15 06:07:20 yamagata Exp $

.include <bsd.own.mk>

PLUGINS=	pppoatm.so
OBJS=		pppoatm.o text2qos.o text2atm.o misc.o ans.o
LIBDIR=		/usr/libexec/ppp

DIST=		${.CURDIR}/../../../../dist/ppp/pppd/plugins/pppoatm
.PATH:		${DIST}

CPPFLAGS+=	-I${DIST}/../.. -I${DIST}/../../../include -I${DIST}

.MAIN: all
all: ${PLUGINS}

${PLUGINS}: ${OBJS}
	${CC} -o ${.TARGET} -shared ${OBJS}

${OBJS}:
	${CC} ${CPPFLAGS} -fPIC -c -o ${.TARGET} ${DIST}/${.TARGET:.o=.c}

install:
	${INSTALL} -c -m ${LIBMODE} -g ${LIBGRP} -o ${LIBOWN} ${PLUGINS} ${DESTDIR}${LIBDIR}

clean:
	rm -f ${PLUGINS} ${OBJS}

cleandir:
