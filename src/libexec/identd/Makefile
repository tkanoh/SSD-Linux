#	$ssdlinux: Makefile,v 1.6 2004/07/03 13:04:43 yamagata Exp $

.include <bsd.own.mk>

PROG=		identd
SRCS=		main.c server.c request.c kernel.c send.c daemon.c \
		safeio.c support.c conf.c str2.c buffer.c timeout.c \
		avail.c pdes.c c_osinfo.c version.c k_linux.c pkvm.c

GENOBJS=	gen_osinfo.o _support.o _safeio.o
CLEANFILES=	gen_osinfo gen_osinfo.o _support.o _safeio.o c_osinfo.c

MAN=		${PROG}.8

DIST=		${.CURDIR}/../../dist/pidentd
.PATH:		${DIST}/src ${DIST}/doc

CPPFLAGS+=	-I${.CURDIR} -I${DIST}/src -DHAVE_CONFIG_H
CPPFLAGS+=	-DPATH_SYSCONFDIR=\"/etc\"
CPPFLAGS+=	-DPATH_PIDFILE=NULL
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../openssl/include
.endif
.if ${TARGET_HOSTTYPE} == "powerpc"
CPPFLAGS+=	-DNOSETGROUPS
.endif
LDADD=		-L${.CURDIR}/../../lib/ssl/libcrypto -lcrypto
LDADD+=         -lpthread

c_osinfo.c: gen_osinfo
	./gen_osinfo > c_osinfo.c

gen_osinfo:
	${HOST_CC} ${CPPFLAGS} -c -o _support.o ${DIST}/src/support.c
	${HOST_CC} ${CPPFLAGS} -c -o _safeio.o ${DIST}/src/safeio.c
	${HOST_CC} ${CPPFLAGS} -c -o gen_osinfo.o ${DIST}/src/gen_osinfo.c
	${HOST_CC} ${CPPFLAGS} -o gen_osinfo gen_osinfo.o _support.o _safeio.o -lpthread -lcrypto

gen_osinfo.o:

.include <bsd.prog.mk>
