#	$ssdlinux: Makefile,v 1.4 2004/08/10 16:01:37 kanoh Exp $

.include <bsd.own.mk>

PROG=		ftpd
SRCS=		cmds.c conf.c ftpd.c ftpcmd.c popen.c cmp.c ls.c \
		print.c util.c
MAN=		${PROG}.8 ftpd.conf.5 ftpusers.5

DIST=		${.CURDIR}/../../../dist/tnftpd
.PATH:		${DIST}/src ${DIST}/ls

CLEANFILES=	ftpcmd.c

.if ${IPV6} == "yes
CPPFLAGS+=	-DHAVE_AF_INET6=1
CPPFLAGS+=	-DHAVE_SOCKADDR_IN6=1
.endif
CPPFLAGS+=	-I${DIST}/src -I${DIST} -I${.CURDIR}/.. -I${DIST}/libnetbsd
CPPFLAGS+=	-DHAVE_TNFTPD_H=1
LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

LDADD+=		-lcrypt
LDADD+=		-L${.CURDIR}/../libnetbsd -lnetbsd
DPADD+=		${.CURDIR}/../libnetbsd/libnetbsd.a
.include "${LIBINET6}/Makefile.ldflags"

NOGCCERROR= 	yes

ftpcmd.c: ${DIST}/src/ftpcmd.y
	yacc ${DIST}/src/ftpcmd.y
	mv -f y.tab.c ftpcmd.c

.include <bsd.prog.mk>
