#	$ssdlinux: Makefile,v 1.6 2004/11/15 06:02:22 yamagata Exp $

.include <bsd.own.mk>

PLUGINS=	radius.so radattr.so radrealms.so
OBJS=		radius.o radattr.o radrealms.o
LIBDIR=		/usr/libexec/ppp

DIST=		${.CURDIR}/../../../../dist/ppp/pppd/plugins/radius
.PATH:          ${DIST}

MAN=		${DIST}/pppd-radius.8 ${DIST}/pppd-radattr.8

CPPFLAGS+=	-I${DIST} -I${DIST}/../.. -I${DIST}/../../../include
CPPFLAGS+=	-DRC_LOG_FACILITY=LOG_DAEMON
CPPFLAGS+=	-DCHAPMS=1 -DMPPE=1 -DMAXOCTETS=1

LIBRADIUSCLIENT= ${.CURDIR}/libradiusclient/libradiusclient.a

.MAIN: all
all: ${PLUGINS}

${PLUGINS}: ${OBJS}
	${CC} -o ${.TARGET} -shared ${.TARGET:.so=.o} ${LIBRADIUSCLIENT}

${OBJS}:
	${CC} ${CPPFLAGS} -c -o ${.TARGET} -fPIC ${DIST}/${.TARGET:.o=.c}

install:
	${INSTALL} -c -m ${LIBMODE} -g ${LIBGRP} -o ${LIBOWN} ${PLUGINS} ${DESTDIR}${LIBDIR}
	${INSTALL} -c -m ${MANMODE} -g ${MANGRP} -o ${MANOWN} ${MAN} ${DESTDIR}${MANDIR}/man8

clean:
	rm -f ${PLUGINS} ${OBJS}

cleandir:

SUBDIR=		libradiusclient

.include <bsd.subdir.mk>
