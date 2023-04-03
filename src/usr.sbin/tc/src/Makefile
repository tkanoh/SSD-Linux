#	$ssdlinux: Makefile,v 1.2 2002/06/06 06:49:01 yamagata Exp $

.include <bsd.own.mk>

PROG=		tc
SRCS=		tc.c tc_qdisc.c tc_class.c tc_filter.c tc_util.c \
		m_police.c m_estimator.c q_fifo.c q_sfq.c q_red.c \
		q_prio.c q_tbf.c q_cbq.c f_rsvp.c f_u32.c f_route.c f_fw.c
MKMAN=		no

DIST=		${.CURDIR}/../../../dist/usagi-tool/src/iproute2/tc
.PATH:		${DIST}

LIBIPROUTE2=	${.CURDIR}/../../../lib/iproute2
.include "${LIBIPROUTE2}/Makefile.cflags"
.include "${LIBIPROUTE2}/Makefile.ldflags"
LDFLAGS+=	-Wl,-export-dynamic
LDADD+=		-L${.CURDIR}/../lib -ltc -lm -ldl
DPADD+=		${.CURDIR}/../lib/libtc.a

NOGCCERROR=	yes

.include <bsd.prog.mk>
