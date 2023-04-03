#	$ssdlinux: Makefile,v 1.7 2004/07/04 05:59:44 yamagata Exp $

.include <bsd.own.mk>

PROG=		telnet
SRCS=		commands.cc main.cc network.cc ring.cc sys_bsd.cc \
		telnet.cc terminal.cc tn3270.cc utilities.cc genget.cc \
		environ.cc netlink.cc

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-telnet
.PATH:		${DIST}/${PROG}

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

CPPFLAGS+=	-fpermissive
CPPFLAGS+=	-DHAVE_TERMCAP_H=1 -DHAVE_LIBNCURSES=1
CPPFLAGS+=	-DUSE_TERMIO -DKLUDGELINEMODE
CPPFLAGS+=	-I${DIST} 
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${.CURDIR}/../../dist/ncurses/include
.endif

.include "${LIBINET6}/Makefile.ldflags"
LIBNCURSES=     ${.CURDIR}/../../lib/libncurses/build/lib
LDDIR!=         cd ${LIBNCURSES} && ${PRINTOBJDIR}
LDADD+=         -L${LDDIR} -lncurses
DPADD+=         ${LIBNCURSES}/libncurses.a
LDADD+=		-lstdc++

NOGCCERROR=	yes

.include <bsd.prog.mk>
