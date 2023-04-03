#	$ssdlinux: Makefile,v 1.6 2004/07/04 05:52:59 yamagata Exp $

.include <bsd.own.mk>

PROG=		ftp
SRCS=		cmds.c cmdtab.c complete.c domacro.c fetch.c ftp.c main.c \
		progressbar.c ruserpass.c util.c

DIST=		${.CURDIR}/../../../dist/tnftp
.PATH:		${DIST}/src

.if ${IPV6} == "yes"
CPPFLAGS+=	-DHAVE_AF_INET6=1
CPPFLAGS+=	-DHAVE_SOCKADDR_IN6=1
CPPFLAGS+=	-DHAVE_IN6ADDRSZ=1
.endif
CPPFLAGS+=	-I${DIST}/src -I${DIST} -I${.CURDIR}/.. -I${DIST}/libedit -I${DIST}/libnetbsd
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${DIST}/../termcap
.endif
LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

LDADD+=         -L${.CURDIR}/../libedit -ledit
LDADD+=         -L${.CURDIR}/../../../lib/libtermcap -ltermcap
LDADD+=		-L${.CURDIR}/../libnetbsd -lnetbsd
DPADD+=         ${.CURDIR}/../libedit/libedit.a
DPADD+=         ${.CURDIR}/../libnetbsd/libnetbsd.a
DPADD+=         ${.CURDIR}/../../../lib/libtermcap/libtermcap.a
LIBINET6=	${.CURDIR}/../../../lib/libinet6
.include "${LIBINET6}/Makefile.ldflags"

NOGCCERROR=	yes

.include <bsd.prog.mk>
