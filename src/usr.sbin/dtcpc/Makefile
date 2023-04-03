#	$ssdlinux: Makefile,v 1.1 2002/11/15 04:25:45 yamagata Exp $

.include <bsd.own.mk>

PROG=		dtcpc
SRCS=		util.c chap.c md5.c dtcp.c nl.c rtsol.c ${PROG}.c 
MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/mkdtcp
.PATH:		${DIST}

LIBIPROUTE2=	${.CURDIR}/../../lib/iproute2
LDADD+=		-L${LIBIPROUTE2}/libnetlink -lnetlink
DPADD+=		${LIBIPROUTE2}/libnetlink/libnetlink.a
 
CPPFLAGS+=	-D_USAGI -DRESOLVE_HOSTNAME
CPPFLAGS+=	-I${DIST} -I${DIST}/../iproute2/include

.include <bsd.prog.mk>
