#	$ssdlinux: Makefile,v 1.5 2004/07/04 07:06:55 yamagata Exp $

.include <bsd.own.mk>

PROG=		syslogd
SRCS=		${PROG}.c pidfile.c
MAN=		sysklogd.8 ${PROG}.8 syslog.conf.5
# syslog.conf install from src/etc
#FILES=		syslog.conf
#FILESDIR=	/etc

DIST=		${.CURDIR}/../../dist/usagi-tool/src/sysklogd	
.PATH:		${DIST}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

CPPFLAGS+=	-DSYSV -fomit-frame-pointer -Wall -fno-strength-reduce \
		-DSYSLOG_INET -DSYSLOG_UNIXAF -DNO_SCCS -DFSSTND \
		-DSYSLOGD_PIDNAME=\"syslogd.pid\" -I$(DIST)

.include "${LIBINET6}/Makefile.ldflags"
CPPFLAGS+=	-DLIBWRAP
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../dist/usagi-tool/src/tcp_wrappers
.endif
LDADD+=		-L${.CURDIR}/../../lib/libwrap -lwrap -lutil
DPADD+=		${.CURDIR}/../../lib/libwrap/libwrap.a ${LIBUTIL}

.include <bsd.prog.mk>
