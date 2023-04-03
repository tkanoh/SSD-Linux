#	$ssdlinux: Makefile,v 1.4 2004/07/04 05:58:39 yamagata Exp $

.include <bsd.own.mk>

PROG=		talk
SRCS=		ctl.c ctl_transact.c display.c get_addrs.c get_names.c \
		init_disp.c invite.c io.c look_up.c msgs.c ctlmsg.c \
		talkaddr.c talk.c

DIST=		${.CURDIR}/../../dist/usagi-tool/src/netkit-ntalk
.PATH:		${DIST}/${PROG} ${DIST}/libtalk ${DIST}/include

LIBINET6=	${.CURDIR}/../../lib/libinet6
.include "${LIBINET6}/Makefile.cflags"

CPPFLAGS+=	-DHAVE_LIBNCURSES=1
CPPFLAGS+=	-I${.CURDIR} -I${DIST} -I${DIST}/include
.if defined(CROSS_BUILD) || defined(NEW_GLIBC)
CPPFLAGS+=	-I${.CURDIR}/../../lib/libncurses/build/include
CPPFLAGS+=	-I${.CURDIR}/../../dist/ncurses/include
.endif
.include "${LIBINET6}/Makefile.ldflags"
LDADD+=		-L${.CURDIR}/../../lib/libncurses/build/lib -lncurses
DPADD+=		${.CURDIR}/../../lib/libncurses/build/lib/libncurses.a

NOGCCERROR=	yes

.include <bsd.prog.mk>
