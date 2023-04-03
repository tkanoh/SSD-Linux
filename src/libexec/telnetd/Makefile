#	$ssdlinux: Makefile,v 1.5 2004/07/03 13:03:08 yamagata Exp $

.include <bsd.own.mk>

PROG=		telnetd
SRCS=		telnetd.c state.c termstat.c slc.c sys_term.c utility.c \
		global.c setproctitle.c

MAN=		issue.net.5 setproctitle.3 telnetd.8

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-telnet
.PATH:		${DIST}/telnetd

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

CPPFLAGS+=	'-DISSUE_FILE="/etc/issue.net"'
CPPFLAGS+=	-DHAVE_LIBNCURSES=1 -DHAVE_LIBTERMCAP=1
CPPFLAGS+=	-DHAVE_LOGWTMP=1 -DHAVE_CURSES_H=1
CPPFLAGS+=	-DHAVE_TERMCAP_H=1 -DPARANOID_TTYS
CPPFLAGS+=	-DNO_REVOKE -DKLUDGELINEMODE
CPPFLAGS+=	-DDIAGNOSTICS
CPPFLAGS+=	-I${DIST} -I${DIST}/telnetd
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${DIST}/../../../ncurses/include
.endif

.include "${LIBINET6}/Makefile.ldflags"
LDADD+=		-L${.CURDIR}/../../lib/libncurses/build/lib -lncurses
LDADD+=		-L${.CURDIR}/../../lib/libtermcap -ltermcap
DPADD+=		${.CURDIR}/../../lib/libncurses/build/lib/libncurses.a
DPADD+=		${.CURDIR}/../../lib/libtermcap/libtermcap.a
LDADD+=         -lutil

NOGCCERROR=	yes

.include <bsd.prog.mk>
